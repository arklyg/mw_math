// Micro Wave Math
// Copyright (c) 2015-2020, Ark Lee
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You must obey the GNU General Public License in all respects for
// all of the code used.  If you modify file(s) with this exception, 
// you may extend this exception to your version of the file(s), but 
// you are not obligated to do so.  If you do not wish to do so, delete 
// this exception statement from your version. If you delete this exception 
// statement from all source files in the program, then also delete it here.
//
// Contact:  Ark Lee <arklee@houduan.online>
//           Beijing, China


#include "mwmathfunction.h"

pthread_cond_t MWMathFunction::_begin_cond;
pthread_cond_t MWMathFunction::_end_cond;
ProcLockable MWMathFunction::_begin_lock;
ProcLockable MWMathFunction::_end_lock;
std::vector<pthread_t> MWMathFunction::_thread_id_vector;
std::vector<size_t> MWMathFunction::_worker_id_vector;
std::vector<bool> MWMathFunction::_work_signal;

size_t MWMathFunction::_finished_count = 0;
const MWMathFunction *MWMathFunction::_work_instance = NULL;
MWMathFunctionFunctionHandleAssignMatrixWithMatrix
MWMathFunction::_AssignValueMatrix_function_pt = NULL;
const MWVector<MWMatrix<MWData> > *MWMathFunction::_input_pt = NULL;
MWVector<MWMatrix<MWData> > *MWMathFunction::_ret_pt = NULL;

bool MWMathFunction::_is_exit = false;

void MWMathFunction::Initialize(size_t thread_num) {
    if (!_thread_id_vector.empty() || thread_num < 1) {
        LOGERROR("(_thread_id_vector.size() = " << _thread_id_vector.size() <<
                 " | (thread_num = " << thread_num << ") < 2, return");
        return;
    }

    pthread_cond_init(&_begin_cond, NULL);
    pthread_cond_init(&_end_cond, NULL);
    _thread_id_vector.resize(thread_num);
    _worker_id_vector.resize(thread_num);
    _work_signal.resize(thread_num, false);
    for (size_t worker_id = 1; worker_id <= thread_num;
            ++ worker_id) { // worker_id 从1开始
        _worker_id_vector[worker_id - 1] = worker_id;
        pthread_create(&_thread_id_vector[worker_id - 1], NULL, Run,
                       &_worker_id_vector[worker_id - 1]);
    }
}

void MWMathFunction::Finalize() {
    for (size_t i = 0; i < _work_signal.size(); ++ i) {
        _work_signal[i] = true;
    }
    _is_exit = true;
    pthread_cond_broadcast(&_begin_cond);

    for (size_t i = 0; i < _thread_id_vector.size(); ++ i) {
        pthread_join(_thread_id_vector[i], NULL);
    }

    _thread_id_vector.clear();
    _worker_id_vector.clear();
    _work_signal.clear();

    pthread_cond_destroy(&_begin_cond);
    pthread_cond_destroy(&_end_cond);
}

void *MWMathFunction::Run(void *arg) {
    const size_t worker_id = *((size_t*) arg);

    LOGTRACE("worker_id = " << worker_id);

    size_t work_size, work_load, off;

    bool is_work;
    while (true) {
        while (true) {
            _begin_lock.Acquire();
            if (!(is_work = _work_signal[worker_id  - 1])) {
                pthread_cond_wait(&_begin_cond, &_begin_lock.GetMutex());
            }
            _begin_lock.Release();

            if (is_work) {
                break;
            }
        }
        _work_signal[worker_id - 1] = false;

        if (_is_exit) {
            break;
        }

        LOGTRACE("got task, worker_id = " << worker_id);

        work_size = _input_pt->size();
        work_load = (work_size % _thread_id_vector.size() == 0 ? work_size /
                     _thread_id_vector.size() : work_size / _thread_id_vector.size() +
                     1); // 向上取整
        off = work_load * (worker_id - 1);
        _work_instance->AssignMultiResult(*_input_pt,
                                            static_cast<MWMathFunctionFunctionHandleAssignMatrixWithMatrix>
                                            (_AssignValueMatrix_function_pt), *_ret_pt, off, work_load);

        LOGTRACE("task done, worker_id = " << worker_id);

        _end_lock.Acquire();
        ++ _finished_count;
        LOGTRACE("(++ _finished_count) = " << _finished_count);

        if (_finished_count >= _thread_id_vector.size()) {
            pthread_cond_broadcast(&_end_cond);
        }
        _end_lock.Release();
    }

    return NULL;
}

MWMathFunction::~MWMathFunction() {
}

MWVector<MWData> MWMathFunction::GetValue(const MWVector<MWData> &input)
const {
    MWVector<MWData> ret = GetValueStructure(input);
    AssignValue(input, ret);
    return ret;
}

MWMatrix<MWData> MWMathFunction::GetValueMatrixStructure(
    const MWMatrix<MWData> &input) const {
    return GetMultiResult(input,
                          static_cast<MWMathFunctionFunctionHandleGetVectorWithVector>
                          (&MWMathFunction::GetValueStructure));
}

MWMatrix<MWData> &MWMathFunction::AssignValueMatrix(const MWMatrix<MWData>
                                                      &input, MWMatrix<MWData> &ret) const {
    return AssignMultiResult(input,
                               static_cast<MWMathFunctionFunctionHandleAssignVectorWithVector>
                               (&MWMathFunction::AssignValue), ret);
}

MWMatrix<MWData> MWMathFunction::GetValueMatrix(const MWMatrix<MWData> &input)
const {
    return GetMultiResult(input,
                          static_cast<MWMathFunctionFunctionHandleGetVectorWithVector>
                          (&MWMathFunction::GetValue));
}

MWVector<MWMatrix<MWData> > MWMathFunction::GetValueVectorMatrixStructure(
    const MWVector<MWMatrix<MWData> > &input) const {
    return GetMultiResult(input,
                          static_cast<MWMathFunctionFunctionHandleGetMatrixWithMatrix>
                          (&MWMathFunction::GetValueMatrixStructure));
}

MWVector<MWMatrix<MWData> > &MWMathFunction::AssignValueVectorMatrix(
    const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret,
    size_t off, size_t len) const {
    return AssignMultiResult(input,
                             static_cast<MWMathFunctionFunctionHandleAssignMatrixWithMatrix>
                             (&MWMathFunction::AssignValueMatrix), ret, off, len);
}

MWVector<MWMatrix<MWData> >
&MWMathFunction::AssignValueVectorMatrixMultiThreadOperation(
    const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret,
    MWMathFunctionFunctionHandleAssignMatrixWithMatrix
    AssignValueMatrix_function_pt) const {
    if (_thread_id_vector.empty()) {
        LOGERROR("_thread_id_vector.empty(), Initialize first");
        return ret;
    }

    _finished_count = 0;
    _work_instance = this;
    _AssignValueMatrix_function_pt = AssignValueMatrix_function_pt;
    _input_pt = &input;
    _ret_pt = &ret;

    _begin_lock.Acquire();
    for (size_t i = 0; i < _work_signal.size(); ++ i) {
        _work_signal[i] = true;
    }
    pthread_cond_broadcast(&_begin_cond);
    _begin_lock.Release();

    bool is_finished;
    while (true) {
        _end_lock.Acquire();
        if (!(is_finished = _finished_count >= _thread_id_vector.size())) {
            pthread_cond_wait(&_end_cond, &_end_lock.GetMutex());
        }
        _end_lock.Release();

        if (is_finished) {
            break;
        }
    }

    return ret;
}

MWVector<MWMatrix<MWData> >
&MWMathFunction::AssignValueVectorMatrixMultiThread(
    const MWVector<MWMatrix<MWData> > &input,
    MWVector<MWMatrix<MWData> > &ret) const {
    return AssignValueVectorMatrixMultiThreadOperation(input, ret,
                                                             &MWMathFunction::AssignValueMatrix);
}

MWVector<MWMatrix<MWData> > MWMathFunction::GetValueVectorMatrix(
    const MWVector<MWMatrix<MWData> > &input) const {
    return GetMultiResult(input,
                            static_cast<MWMathFunctionFunctionHandleGetMatrixWithMatrix>
                            (&MWMathFunction::GetValueMatrix));
}

MWMatrix<MWData> &MWMathFunction::AssignMultiResult(const MWMatrix<MWData>
                                                    &input, const MWMathFunctionFunctionHandleAssignVectorWithVector
                                                    function_handle, MWMatrix<MWData> &ret) const {
    for (size_t i = 0; i < input.GetRowNum(); ++ i) {
        (this->*function_handle)(input._data[i], ret._data[i]);
    }
    return ret;
}

MWMatrix<MWData> MWMathFunction::GetMultiResult(const MWMatrix<MWData> &input,
                                                const MWMathFunctionFunctionHandleGetVectorWithVector function_handle) const {
    MWMatrix<MWData> ret;
    for (size_t i = 0; i < input.GetRowNum(); ++ i) {
        ret.AddRow((this->*function_handle)(input._data[i]));
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &MWMathFunction::AssignMultiResult(
    const MWVector<MWMatrix<MWData> > &input,
    const MWMathFunctionFunctionHandleAssignMatrixWithMatrix function_handle,
    MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len) const {
    // 计算到结尾
    if (len == 0) {
        len = (off > input.size() ? 0 : input.size() - off);
    }

    for (size_t i = off; i < off + len && i < input.size(); ++ i) {
        (this->*function_handle)(input[i], ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > MWMathFunction::GetMultiResult(
    const MWVector<MWMatrix<MWData> > &input,
    const MWMathFunctionFunctionHandleGetMatrixWithMatrix function_handle) const {
    MWVector<MWMatrix<MWData> > ret(input.size());
    for (size_t i = 0; i < input.size(); ++ i) {
        ret[i] = (this->*function_handle)(input[i]);
    }

    return ret;
}
