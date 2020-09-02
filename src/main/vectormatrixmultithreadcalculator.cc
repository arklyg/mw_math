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


#include "vectormatrixmultithreadcalculator.h"

pthread_cond_t VectorMatrixMultiThreadCalculator::_start_cond;
pthread_cond_t VectorMatrixMultiThreadCalculator::_finish_cond;
ProcLockable VectorMatrixMultiThreadCalculator::_start_lock;
ProcLockable VectorMatrixMultiThreadCalculator::_finish_lock;
std::vector<pthread_t> VectorMatrixMultiThreadCalculator::_thread_id_vector;
std::vector<size_t> VectorMatrixMultiThreadCalculator::_worker_id_vector;
std::vector<bool> VectorMatrixMultiThreadCalculator::_start_signal_vector;

size_t VectorMatrixMultiThreadCalculator::_finished_count = 0;
VectorMatrixMultiThreadCalculatorFunction VectorMatrixMultiThreadCalculator::_function;
const MWVector<MWMatrix<MWData> > *VectorMatrixMultiThreadCalculator::_vector_matrix_pt_1 = NULL;
const MWVector<MWMatrix<MWData> > *VectorMatrixMultiThreadCalculator::_vector_matrix_pt_2 = NULL;
const MWMatrix<MWData> *VectorMatrixMultiThreadCalculator::_matrix_pt_1 = NULL;
const MWData *VectorMatrixMultiThreadCalculator::_data_pt_1 = NULL;
MWVector<MWMatrix<MWData> > *VectorMatrixMultiThreadCalculator::_ret_pt = NULL;

bool VectorMatrixMultiThreadCalculator::_is_exit = false;

MWVector<MWVector<MWMatrix<MWData> > > &VectorMatrixMultiThreadCalculator::AssignTimesTransformed(
    const MWVector<MWVector<MWMatrix<MWData> > > &v_m1,
    const MWVector<MWVector<MWMatrix<MWData> > > &v_m2,
    MWVector<MWVector<MWMatrix<MWData> > > &ret) {
    if (v_m1.size() != v_m2.size()) {
        LOGERROR("(v_m1.size() = " << v_m1.size() << 
                 ") != (v_m2.size() = " << v_m2.size() << 
                 "), can not do AssignTimesTransformed, return");
        return ret;
    }

    for (size_t i = 0; i < v_m1.size(); ++ i) {
        VectorMatrixMultiThreadCalculator::AssignTimesTransformed(v_m1[i], v_m2[i], ret[i]);
    }

    return ret;
}

int VectorMatrixMultiThreadCalculator::AssignWorkDescription(size_t worker_id,
                                                             size_t work_size, 
                                                             size_t &off, 
                                                             size_t &work_load) {
    work_load = work_size % _thread_id_vector.size() == 0 ?
                (work_size / _thread_id_vector.size()) :
                (work_size / _thread_id_vector.size() + 1); // 向上取整
    if (work_load == 0) {
        return -1;
    }

    off = work_load * (worker_id - 1);
    if (off >= work_size) {
        return -1;
    }

    return 1;
}

void *VectorMatrixMultiThreadCalculator::Run(void *arg) {
    const size_t worker_id = *((size_t*) arg);

    LOGTRACE("worker_id = " << worker_id);

    while (true) {
        _start_lock.Acquire();
        if (!_start_signal_vector[worker_id  - 1]) {
            pthread_cond_wait(&_start_cond, &_start_lock.GetMutex());
        }
        _start_lock.Release();

        _start_signal_vector[worker_id - 1] = false;

        if (_is_exit) {
            break;
        }

        LOGTRACE("got task, worker_id = " << worker_id);

        size_t off, len;
        if (AssignWorkDescription(worker_id, _vector_matrix_pt_1->size(), off,
                                    len) > 0) {
            if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignPlus222) {
                ::AssignPlus(*_vector_matrix_pt_1, *_vector_matrix_pt_2, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignMinus222) {
                ::AssignMinus(*_vector_matrix_pt_1, *_vector_matrix_pt_2, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignTimes222) {
                ::AssignTimes(*_vector_matrix_pt_1, *_vector_matrix_pt_2, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignTimesTransFormed222) {
                ::AssignTimesTransformed(*_vector_matrix_pt_1, *_vector_matrix_pt_2, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignDiagonaledTimesTransformed222) {
                ::AssignDiagonaledTimesTransformed(*_vector_matrix_pt_1, *_vector_matrix_pt_2, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignDiagonaledTimes222) {
                ::AssignDiagonaledTimes(*_vector_matrix_pt_1, *_vector_matrix_pt_2, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignPlus221) {
                ::AssignPlus(*_vector_matrix_pt_1, *_matrix_pt_1, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignTimes221) {
                ::AssignTimes(*_vector_matrix_pt_1, *_matrix_pt_1, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignDiagonaledTimes221) {
                ::AssignDiagonaledTimesTransformed(*_vector_matrix_pt_1, *_matrix_pt_1, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignTimes220) {
                ::AssignTimes(*_vector_matrix_pt_1, *_data_pt_1, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignTimes212) {
                ::AssignTimes(*_matrix_pt_1, *_vector_matrix_pt_1, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignSquare22) {
                ::AssignSquare(*_vector_matrix_pt_1, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssign22) {
                ::Assign(*_vector_matrix_pt_1, *_ret_pt, off, len);
            } else if (_function == VectorMatrixMultiThreadCalculatorFunctionAssignSum22) {
                ::AssignSum(*_vector_matrix_pt_1, (*_ret_pt)[off / len], off, len);
            }
        }

        LOGTRACE("task done, worker_id = " << worker_id);

        _finish_lock.Acquire();
        ++ _finished_count;
        LOGTRACE("(++ _finished_count) = " << _finished_count);

        if (_finished_count >= _thread_id_vector.size()) {
            pthread_cond_broadcast(&_finish_cond);
        }
        _finish_lock.Release();
    }

    return NULL;
}

MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignOperateMultiThread() {
    if (_thread_id_vector.empty()) {
        LOGERROR("_thread_id_vector.empty(), Initialize first");
        return *_ret_pt;
    }

    _finished_count = 0;

    _start_lock.Acquire();
    for (size_t i = 0; i < _start_signal_vector.size(); ++ i) {
        _start_signal_vector[i] = true;
    }
    pthread_cond_broadcast(&_start_cond);
    _start_lock.Release();

    _finish_lock.Acquire();
    if (_finished_count < _thread_id_vector.size()) {
        pthread_cond_wait(&_finish_cond, &_finish_lock.GetMutex());
    }
    _finish_lock.Release();

    return *_ret_pt;
}

void VectorMatrixMultiThreadCalculator::Initialize(size_t thread_num) {
    if (!_thread_id_vector.empty() || thread_num < 1) {
        LOGERROR("(_thread_id_vector.size() = " << _thread_id_vector.size() <<
                 " | (thread_num = " << thread_num << 
                 ") < 2, return");
        return;
    }

    pthread_cond_init(&_start_cond, NULL);
    pthread_cond_init(&_finish_cond, NULL);
    _thread_id_vector.resize(thread_num);
    _worker_id_vector.resize(thread_num);
    _start_signal_vector.resize(thread_num, false);
    for (size_t worker_id = 1; worker_id <= thread_num; ++worker_id) { // worker_id 从1开始
        _worker_id_vector[worker_id - 1] = worker_id;
        pthread_create(&_thread_id_vector[worker_id - 1], 
                       NULL, 
                       Run,
                       &_worker_id_vector[worker_id - 1]);
    }
}

void VectorMatrixMultiThreadCalculator::Finalize() {
    _is_exit = true;

    for (size_t i = 0; i < _start_signal_vector.size(); ++ i) {
        _start_signal_vector[i] = true;
    }
    _start_lock.Acquire();
    pthread_cond_broadcast(&_start_cond);
    _start_lock.Release();

    for (size_t i = 0; i < _thread_id_vector.size(); ++ i) {
        pthread_join(_thread_id_vector[i], NULL);
    }

    _thread_id_vector.clear();
    _worker_id_vector.clear();
    _start_signal_vector.clear();

    pthread_cond_destroy(&_start_cond);
    pthread_cond_destroy(&_finish_cond);
}

