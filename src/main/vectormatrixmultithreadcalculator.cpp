#include "vectormatrixmultithreadcalculator.h"

pthread_cond_t VectorMatrixMultiThreadCalculator::_start_cond;
pthread_cond_t VectorMatrixMultiThreadCalculator::_finish_cond;
ProcLockable VectorMatrixMultiThreadCalculator::_start_lock;
ProcLockable VectorMatrixMultiThreadCalculator::_finish_lock;
vector<pthread_t> VectorMatrixMultiThreadCalculator::_thread_id_vector;
vector<size_t> VectorMatrixMultiThreadCalculator::_worker_id_vector;
vector<bool> VectorMatrixMultiThreadCalculator::_start_signal_vector;

size_t VectorMatrixMultiThreadCalculator::_finished_count = 0;
VectorMatrixMultiThreadCalculatorFunctionType VectorMatrixMultiThreadCalculator::_function_type;
void* VectorMatrixMultiThreadCalculator::_function_handle = NULL;
vector<const void*> VectorMatrixMultiThreadCalculator::_arg_pt_vector(VECTORMATRIXMULTITHREADCALCULATOR_FUNCTION_ARG_COUNT_MAX, NULL);
MWVector<MWMatrix<MWData> >* VectorMatrixMultiThreadCalculator::_ret_pt = NULL;

bool VectorMatrixMultiThreadCalculator::_is_exit = false;


MWVector<MWVector<MWMatrix<MWData> > > &VectorMatrixMultiThreadCalculator::assign_times_transformed(const MWVector<MWVector<MWMatrix<MWData> > > &v_m1, const MWVector<MWVector<MWMatrix<MWData> > > &v_m2, MWVector<MWVector<MWMatrix<MWData> > > &ret)
{
	if (v_m1.size() != v_m2.size())
	{
		LOG_ERROR(_logger, "(v_m1.size() = " << v_m1.size() << ") != (v_m2.size() = " << v_m2.size() << "), can not do, return");
		return ret;
	}

	for (size_t i = 0; i < v_m1.size(); ++ i)
	{
		VectorMatrixMultiThreadCalculator::assign_times_transformed(v_m1[i], v_m2[i], ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_plus_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_plus(v1, v2, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_minus_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_minus(v1, v2, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_times(v1, v2, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times_transformed_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_times_transformed(v1, v2, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_diagonaled_times_transformed_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_diagonaled_times_transformed(v1, v2, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_diagonaled_times_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_diagonaled_times(v1, v2, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_plus_221(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_plus(v, m, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times_221(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_times(v, m, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_diagonaled_times_transformed_221(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_diagonaled_times_transformed(v, m, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times_220(const MWVector<MWMatrix<MWData> > &v, const MWData &scale, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_times(v, scale, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times_212(const MWMatrix<MWData> &m, const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_times(m, v, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_square_22(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign_square(v, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_22(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	return ::assign(v, ret, off, len);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_sum_22(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &mid_ret, size_t off, size_t len)
{
	::assign_sum(v, mid_ret[off / len], off, len);
	return mid_ret;
}

void VectorMatrixMultiThreadCalculator::assign_work_description(size_t worker_id, size_t work_size, size_t &off, size_t &work_load)
{
	work_load = (work_size % _thread_id_vector.size() == 0 ? work_size / _thread_id_vector.size() : work_size / _thread_id_vector.size() + 1); // 向上取整
	off = work_load * (worker_id - 1);
}

void VectorMatrixMultiThreadCalculator::assign_operation_222(void* function_handle, size_t worker_id)
{
	const MWVector<MWMatrix<MWData> > &v1 = * ((MWVector<MWMatrix<MWData> >*) _arg_pt_vector[0]);
	size_t off, work_load;
	assign_work_description(worker_id, v1.size(), off, work_load);
	(* ((AssignFunction222Pt) function_handle))(v1, * ((MWVector<MWMatrix<MWData> >*) _arg_pt_vector[1]), * _ret_pt, off, work_load);
}

void VectorMatrixMultiThreadCalculator::assign_operation_221(void* function_handle, size_t worker_id)
{
	const MWVector<MWMatrix<MWData> > &v1 = * ((MWVector<MWMatrix<MWData> >*) _arg_pt_vector[0]);
	size_t off, work_load;
	assign_work_description(worker_id, v1.size(), off, work_load);
	(* ((AssignFunction221Pt) function_handle))(v1, * ((MWMatrix<MWData>*) _arg_pt_vector[1]), * _ret_pt, off, work_load);
}

void VectorMatrixMultiThreadCalculator::assign_operation_220(void* function_handle, size_t worker_id)
{
	const MWVector<MWMatrix<MWData> > &v1 = * ((MWVector<MWMatrix<MWData> >*) _arg_pt_vector[0]);
	size_t off, work_load;
	assign_work_description(worker_id, v1.size(), off, work_load);
	(* ((AssignFunction220Pt) function_handle))(v1, * ((MWData*) _arg_pt_vector[1]), * _ret_pt, off, work_load);
}

void VectorMatrixMultiThreadCalculator::assign_operation_212(void* function_handle, size_t worker_id)
{
	const MWVector<MWMatrix<MWData> > &v2 = * ((MWVector<MWMatrix<MWData> >*) _arg_pt_vector[1]);
	size_t off, work_load;
	assign_work_description(worker_id, v2.size(), off, work_load);
	(* ((AssignFunction212Pt) function_handle))(* ((MWMatrix<MWData>*) _arg_pt_vector[0]), v2, * _ret_pt, off, work_load);
}

void VectorMatrixMultiThreadCalculator::assign_operation_22(void* function_handle, size_t worker_id)
{
	const MWVector<MWMatrix<MWData> > &v1 = * ((MWVector<MWMatrix<MWData> >*) _arg_pt_vector[0]);
	size_t off, work_load;
	assign_work_description(worker_id, v1.size(), off, work_load);
	(* ((AssignFunction22Pt) function_handle))(v1, * _ret_pt, off, work_load);
}

void* VectorMatrixMultiThreadCalculator::run(void* arg)
{
	const size_t worker_id = * ((size_t*) arg);

	LOG_TRACE(_logger, "worker_id = " << worker_id);

	while (true)
	{
		_start_lock.acquire();
		if (!_start_signal_vector[worker_id  - 1])
		{
			pthread_cond_wait(& _start_cond, & _start_lock.get_mutex());
		}
		_start_lock.release();
		/*
		while (true)
		{
			_start_lock.acquire();
			if (!(is_work = _start_signal_vector[worker_id  - 1]))
			{
				pthread_cond_wait(& _start_cond, & _start_lock.get_mutex());
			}
			_start_lock.release();

			if (is_work)
			{
				break;
			}
		}
		*/

		_start_signal_vector[worker_id - 1] = false;

		if (_is_exit)
		{
			break;
		}

		LOG_TRACE(_logger, "got task, worker_id = " << worker_id);

		if (_function_type == VectorMatrixMultiThreadCalculatorFunctionType222)
		{
			assign_operation_222(_function_handle, worker_id);
		}
		else if (_function_type == VectorMatrixMultiThreadCalculatorFunctionType221)
		{
			assign_operation_221(_function_handle, worker_id);
		}
		else if (_function_type == VectorMatrixMultiThreadCalculatorFunctionType220)
		{
			assign_operation_220(_function_handle, worker_id);
		}
		else if (_function_type == VectorMatrixMultiThreadCalculatorFunctionType212)
		{
			assign_operation_212(_function_handle, worker_id);
		}
		else if (_function_type == VectorMatrixMultiThreadCalculatorFunctionType22)
		{
			assign_operation_22(_function_handle, worker_id);
		}
		else
		{
			LOG_ERROR(_logger, "function type error");
		}

		LOG_TRACE(_logger, "task done, worker_id = " << worker_id);

		_finish_lock.acquire();
		++ _finished_count;
		LOG_TRACE(_logger, "(++ _finished_count) = " << _finished_count);

		if (_finished_count >= _thread_id_vector.size())
		{
			pthread_cond_broadcast(& _finish_cond);
		}
		_finish_lock.release();
	}

	return NULL;
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType function_type, void* function_handle, const void* v1_pt, const void* v2_pt, MWVector<MWMatrix<MWData> >* ret_pt)
{
	if (_thread_id_vector.empty())
	{
		LOG_ERROR(_logger, "_thread_id_vector.empty(), initialize first");
		return * ret_pt;
	}

	_finished_count = 0;
	_function_type = function_type;
	_function_handle = function_handle;
	_arg_pt_vector[0] = v1_pt;
	_arg_pt_vector[1] = v2_pt;
	_ret_pt = ret_pt;

	_start_lock.acquire();
	for (size_t i = 0; i < _start_signal_vector.size(); ++ i)
	{
		_start_signal_vector[i] = true;
	}
	pthread_cond_broadcast(& _start_cond);
	_start_lock.release();

	_finish_lock.acquire();
	if (_finished_count < _thread_id_vector.size())
	{
		pthread_cond_wait(& _finish_cond, & _finish_lock.get_mutex());
	}
	_finish_lock.release();

	/*
	while (true)
	{
		_finish_lock.acquire();
		if (!(is_finished = _finished_count >= _thread_id_vector.size()))
		{
			pthread_cond_wait(& _finish_cond, & _finish_lock.get_mutex());
		}
		_finish_lock.release();

		if (is_finished)
		{
			break;
		}
	}
	*/

	return * ret_pt;
}

void VectorMatrixMultiThreadCalculator::initialize(size_t thread_num)
{
	if (!_thread_id_vector.empty() || thread_num < 1)
	{
		LOG_ERROR(_logger, "(_thread_id_vector.size() = " << _thread_id_vector.size() << " | (thread_num = " << thread_num << ") < 2, return");
		return;
	}

	pthread_cond_init(& _start_cond, NULL);
	pthread_cond_init(& _finish_cond, NULL);
	_thread_id_vector.resize(thread_num);
	_worker_id_vector.resize(thread_num);
	_start_signal_vector.resize(thread_num, false);
	for (size_t worker_id = 1; worker_id <= thread_num; ++ worker_id) // worker_id 从1开始
	{
		_worker_id_vector[worker_id - 1] = worker_id;
		pthread_create(& _thread_id_vector[worker_id - 1], NULL, run, & _worker_id_vector[worker_id - 1]);
	}
}

void VectorMatrixMultiThreadCalculator::finalize()
{
	_is_exit = true;

	for (size_t i = 0; i < _start_signal_vector.size(); ++ i)
	{
		_start_signal_vector[i] = true;
	}
	_start_lock.acquire();
	pthread_cond_broadcast(& _start_cond);
	_start_lock.release();

	for (size_t i = 0; i < _thread_id_vector.size(); ++ i)
	{
		pthread_join(_thread_id_vector[i], NULL);
	}

	_thread_id_vector.clear();
	_worker_id_vector.clear();
	_start_signal_vector.clear();

	pthread_cond_destroy(& _start_cond);
	pthread_cond_destroy(& _finish_cond);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_plus(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType222, (void*) (& assign_plus_222), (const void*) (& v1), (const void*) (& v2), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_minus(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType222, (void*) (& assign_minus_222), (const void*) (& v1), (const void*) (& v2), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType222, (void*) (& assign_times_222), (const void*) (& v1), (const void*) (& v2), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times_transformed(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType222, (void*) (& assign_times_transformed_222), (const void*) (& v1), (const void*) (& v2), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_diagonaled_times_transformed(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType222, (void*) (& assign_diagonaled_times_transformed_222), (const void*) (& v1), (const void*) (& v2), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_diagonaled_times(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType222, (void*) (& assign_diagonaled_times_222), (const void*) (& v1), (const void*) (& v2), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_plus(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType221, (void*) (& assign_plus_221), (const void*) (& v), (const void*) (& m), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType221, (void*) (& assign_times_221), (const void*) (& v), (const void*) (& m), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_diagonaled_times_transformed(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType221, (void*) (& assign_diagonaled_times_transformed_221), (const void*) (& v), (const void*) (& m), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times(const MWVector<MWMatrix<MWData> > &v, const MWData &scale, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType220, (void*) (& assign_times_220), (const void*) (& v), (const void*) (& scale), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_times(const MWMatrix<MWData> &m, const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType212, (void*) (& assign_times_212), (const void*) (& m), (const void*) (& v), & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign_square(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType22, (void*) (& assign_square_22), (const void*) (& v), NULL, & ret);
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::assign(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret)
{
	return assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType22, (void*) (& assign_22), (const void*) (& v), NULL, & ret);
}

MWMatrix<MWData> &VectorMatrixMultiThreadCalculator::assign_sum(const MWVector<MWMatrix<MWData> > &v, MWMatrix<MWData> &ret)
{
	MWVector<MWMatrix<MWData> > mid_ret(_thread_id_vector.size(), ret);

	assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType22, (void*) (& assign_sum_22), (const void*) (& v), NULL, & mid_ret);

	return ::assign_sum(mid_ret, ret);
}
