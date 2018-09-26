#include "mwmathfunction.h"

pthread_cond_t MWMathFunction::_start_cond;
pthread_cond_t MWMathFunction::_end_cond;
ProcLockable MWMathFunction::_start_lock;
// ProcLockable MWMathFunction::_finished_lock;
ProcLockable MWMathFunction::_end_lock;
vector<pthread_t> MWMathFunction::_thread_id_vector;
vector<size_t> MWMathFunction::_worker_id_vector;
vector<bool> MWMathFunction::_work_signal;

size_t MWMathFunction::_finished_count = 0;
const MWMathFunction* MWMathFunction::_work_instance = NULL;
MWMathFunctionFunctionHandleAssignMatrixWithMatrix MWMathFunction::_assign_value_matrix_function_pt = NULL;
const MWVector<MWMatrix<MWData> >* MWMathFunction::_input_pt = NULL;
MWVector<MWMatrix<MWData> >* MWMathFunction::_ret_pt = NULL;

bool MWMathFunction::_is_exit = false;

void MWMathFunction::initialize(size_t thread_num)
{
	if (!_thread_id_vector.empty() || thread_num < 1)
	{
		LOG_ERROR(_logger, "(_thread_id_vector.size() = " << _thread_id_vector.size() << " | (thread_num = " << thread_num << ") < 2, return");
		return;
	}

	pthread_cond_init(& _start_cond, NULL);
	pthread_cond_init(& _end_cond, NULL);
	_thread_id_vector.resize(thread_num);
	_worker_id_vector.resize(thread_num);
	_work_signal.resize(thread_num, false);
	for (size_t worker_id = 1; worker_id <= thread_num; ++ worker_id) // worker_id 从1开始
	{
		_worker_id_vector[worker_id - 1] = worker_id;
		pthread_create(& _thread_id_vector[worker_id - 1], NULL, run, & _worker_id_vector[worker_id - 1]);
	}
}

void MWMathFunction::finalize()
{
	for (size_t i = 0; i < _work_signal.size(); ++ i)
	{
		_work_signal[i] = true;
	}
	_is_exit = true;
	pthread_cond_broadcast(& _start_cond);

	for (size_t i = 0; i < _thread_id_vector.size(); ++ i)
	{
		pthread_join(_thread_id_vector[i], NULL);
	}

	_thread_id_vector.clear();
	_worker_id_vector.clear();
	_work_signal.clear();

	pthread_cond_destroy(& _start_cond);
	pthread_cond_destroy(& _end_cond);
}

void* MWMathFunction::run(void* arg)
{
	const size_t worker_id = * ((size_t*) arg);

	LOG_TRACE(_logger, "worker_id = " << worker_id);

	size_t work_size, work_load, off;

	bool is_work;
	while (true)
	{
		while (true)
		{
			_start_lock.acquire();
			if (!(is_work = _work_signal[worker_id  - 1]))
			{
				pthread_cond_wait(& _start_cond, & _start_lock.get_mutex());
			}
			_start_lock.release();

			if (is_work)
			{
				break;
			}
		}
		_work_signal[worker_id - 1] = false;

		if (_is_exit)
		{
			break;
		}

		LOG_TRACE(_logger, "got task, worker_id = " << worker_id);

		work_size = _input_pt->size();
		work_load = (work_size % _thread_id_vector.size() == 0 ? work_size / _thread_id_vector.size() : work_size / _thread_id_vector.size() + 1); // 向上取整
		off = work_load * (worker_id - 1);
		_work_instance->assign_multi_result(* _input_pt, static_cast<MWMathFunctionFunctionHandleAssignMatrixWithMatrix>(_assign_value_matrix_function_pt), * _ret_pt, off, work_load);

		LOG_TRACE(_logger, "task done, worker_id = " << worker_id);

		_end_lock.acquire();
		++ _finished_count;
		LOG_TRACE(_logger, "(++ _finished_count) = " << _finished_count);

		if (_finished_count >= _thread_id_vector.size())
		{
			pthread_cond_broadcast(& _end_cond);
		}
		_end_lock.release();
	}

	return NULL;
}

MWMathFunction::~MWMathFunction()
{
}

MWVector<MWData> MWMathFunction::get_value(const MWVector<MWData> &input) const
{
	MWVector<MWData> ret = get_value_structure(input);
	assign_value(input, ret);
	return ret;
}

MWMatrix<MWData> MWMathFunction::get_value_matrix_structure(const MWMatrix<MWData> &input) const
{
	return get_multi_result(input, static_cast<MWMathFunctionFunctionHandleGetVectorWithVector>(& MWMathFunction::get_value_structure));
}

MWMatrix<MWData> &MWMathFunction::assign_value_matrix(const MWMatrix<MWData> &input, MWMatrix<MWData> &ret) const
{
	return assign_multi_result(input, static_cast<MWMathFunctionFunctionHandleAssignVectorWithVector>(& MWMathFunction::assign_value), ret);
}

MWMatrix<MWData> MWMathFunction::get_value_matrix(const MWMatrix<MWData> &input) const
{
	return get_multi_result(input, static_cast<MWMathFunctionFunctionHandleGetVectorWithVector>(& MWMathFunction::get_value));
}

MWVector<MWMatrix<MWData> > MWMathFunction::get_value_vector_matrix_structure(const MWVector<MWMatrix<MWData> > &input) const
{
	return get_multi_result(input, static_cast<MWMathFunctionFunctionHandleGetMatrixWithMatrix>(& MWMathFunction::get_value_matrix_structure));
}

MWVector<MWMatrix<MWData> > &MWMathFunction::assign_value_vector_matrix(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len) const
{
	return assign_multi_result(input, static_cast<MWMathFunctionFunctionHandleAssignMatrixWithMatrix>(& MWMathFunction::assign_value_matrix), ret, off, len);
}

MWVector<MWMatrix<MWData> > &MWMathFunction::assign_value_vector_matrix_multi_thread_operation(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret, MWMathFunctionFunctionHandleAssignMatrixWithMatrix assign_value_matrix_function_pt) const
{
	if (_thread_id_vector.empty())
	{
		LOG_ERROR(_logger, "_thread_id_vector.empty(), initialize first");
		return ret;
	}

	_finished_count = 0;
	_work_instance = this;
	_assign_value_matrix_function_pt = assign_value_matrix_function_pt;
	_input_pt = & input;
	_ret_pt = & ret;

	_start_lock.acquire();
	for (size_t i = 0; i < _work_signal.size(); ++ i)
	{
		_work_signal[i] = true;
	}
	pthread_cond_broadcast(& _start_cond);
	_start_lock.release();

	bool is_finished;
	while (true)
	{
		_end_lock.acquire();
		if (!(is_finished = _finished_count >= _thread_id_vector.size()))
		{
			pthread_cond_wait(& _end_cond, & _end_lock.get_mutex());
		}
		_end_lock.release();

		if (is_finished)
		{
			break;
		}
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &MWMathFunction::assign_value_vector_matrix_multi_thread(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret) const
{
	return assign_value_vector_matrix_multi_thread_operation(input, ret, & MWMathFunction::assign_value_matrix);
}

MWVector<MWMatrix<MWData> > MWMathFunction::get_value_vector_matrix(const MWVector<MWMatrix<MWData> > &input) const
{
	return get_multi_result(input, static_cast<MWMathFunctionFunctionHandleGetMatrixWithMatrix>(& MWMathFunction::get_value_matrix));
}

MWMatrix<MWData> &MWMathFunction::assign_multi_result(const MWMatrix<MWData> &input, const MWMathFunctionFunctionHandleAssignVectorWithVector function_handle, MWMatrix<MWData> &ret) const
{
	for (size_t i = 0; i < input.get_row_num(); ++ i)
	{
		(this->*function_handle)(input._data[i], ret._data[i]);
	}
	return ret;
}

MWMatrix<MWData> MWMathFunction::get_multi_result(const MWMatrix<MWData> &input, const MWMathFunctionFunctionHandleGetVectorWithVector function_handle) const
{
	MWMatrix<MWData> ret;
	for (size_t i = 0; i < input.get_row_num(); ++ i)
	{
		ret.add_row((this->*function_handle)(input._data[i]));
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &MWMathFunction::assign_multi_result(const MWVector<MWMatrix<MWData> > &input, const MWMathFunctionFunctionHandleAssignMatrixWithMatrix function_handle, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len) const
{
	// 计算到结尾
	if (len == 0)
	{
		len = (off > input.size() ? 0 : input.size() - off);
	}

	for (size_t i = off; i < off + len && i < input.size(); ++ i)
	{
		(this->*function_handle)(input[i], ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > MWMathFunction::get_multi_result(const MWVector<MWMatrix<MWData> > &input, const MWMathFunctionFunctionHandleGetMatrixWithMatrix function_handle) const
{
	MWVector<MWMatrix<MWData> > ret(input.size());
	for (size_t i = 0; i < input.size(); ++ i)
	{
		ret[i] = (this->*function_handle)(input[i]);
	}

	return ret;
}

