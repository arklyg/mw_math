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


#include <proclockable.h>
#include "mwmatrixhelper.h"

#define VECTORMATRIXMULTITHREADCALCULATOR_FUNCTION_ARG_COUNT_MAX 2

enum VectorMatrixMultiThreadCalculatorFunction {
    VectorMatrixMultiThreadCalculatorFunctionAssignPlus222,
    VectorMatrixMultiThreadCalculatorFunctionAssignMinus222,
    VectorMatrixMultiThreadCalculatorFunctionAssignTimes222,
    VectorMatrixMultiThreadCalculatorFunctionAssignTimesTransFormed222,
    VectorMatrixMultiThreadCalculatorFunctionAssignDiagonaledTimesTransformed222,
    VectorMatrixMultiThreadCalculatorFunctionAssignDiagonaledTimes222,
    VectorMatrixMultiThreadCalculatorFunctionAssignPlus221,
    VectorMatrixMultiThreadCalculatorFunctionAssignTimes221,
    VectorMatrixMultiThreadCalculatorFunctionAssignDiagonaledTimes221,
    VectorMatrixMultiThreadCalculatorFunctionAssignTimes220,
    VectorMatrixMultiThreadCalculatorFunctionAssignTimes212,
    VectorMatrixMultiThreadCalculatorFunctionAssignSquare22,
    VectorMatrixMultiThreadCalculatorFunctionAssign22,
    VectorMatrixMultiThreadCalculatorFunctionAssignSum22,
};

class VectorMatrixMultiThreadCalculator {
  private:
    static pthread_cond_t _start_cond;
    static pthread_cond_t _finish_cond;
    static ProcLockable _start_lock;
    static ProcLockable _finish_lock;
    static std::vector<pthread_t> _thread_id_vector;
    static std::vector<size_t> _worker_id_vector;
    static std::vector<bool> _start_signal_vector;

    static size_t _finished_count;
    static VectorMatrixMultiThreadCalculatorFunction _function;
    static const MWVector<MWMatrix<MWData> > *_vector_matrix_pt_1;
    static const MWVector<MWMatrix<MWData> > *_vector_matrix_pt_2;
    static const MWMatrix<MWData> *_matrix_pt_1;
    static const MWData *_data_pt_1;
    static MWVector<MWMatrix<MWData> > *_ret_pt;

    static bool _is_exit;

  private:
    static int AssignWorkDescription(size_t worker_id, 
                                     size_t work_size,
                                     size_t &off, 
                                     size_t &work_load);
    static void *Run(void *arg);
    static MWVector<MWMatrix<MWData> > &AssignOperateMultiThread();

  public:
    static void Initialize(size_t thread_num);
    static void Finalize();

    static MWVector<MWVector<MWMatrix<MWData> > > &AssignTimesTransformed(
        const MWVector<MWVector<MWMatrix<MWData> > > &v_m1,
        const MWVector<MWVector<MWMatrix<MWData> > > &v_m2,
        MWVector<MWVector<MWMatrix<MWData> > > &ret);

    inline static MWVector<MWMatrix<MWData> > &AssignPlus(
        const MWVector<MWMatrix<MWData> > &v1, 
        const MWVector<MWMatrix<MWData> > &v2,
        MWVector<MWMatrix<MWData> > &ret);
    inline static MWVector<MWMatrix<MWData> > &AssignMinus(
        const MWVector<MWMatrix<MWData> > &v1, 
        const MWVector<MWMatrix<MWData> > &v2,
        MWVector<MWMatrix<MWData> > &ret);
    inline static MWVector<MWMatrix<MWData> > &AssignTimes(
        const MWVector<MWMatrix<MWData> > &v1, 
        const MWVector<MWMatrix<MWData> > &v2,
        MWVector<MWMatrix<MWData> > &ret);
    inline static MWVector<MWMatrix<MWData> > &AssignTimesTransformed(
        const MWVector<MWMatrix<MWData> > &v1, 
        const MWVector<MWMatrix<MWData> > &v2,
        MWVector<MWMatrix<MWData> > &ret);
    inline static MWVector<MWMatrix<MWData> > &AssignDiagonaledTimesTransformed(
        const MWVector<MWMatrix<MWData> > &v1, 
        const MWVector<MWMatrix<MWData> > &v2,
        MWVector<MWMatrix<MWData> > &ret);
    inline static MWVector<MWMatrix<MWData> > &AssignDiagonaledTimes(
        const MWVector<MWMatrix<MWData> > &v1, 
        const MWVector<MWMatrix<MWData> > &v2,
        MWVector<MWMatrix<MWData> > &ret);

    inline static MWVector<MWMatrix<MWData> > &AssignPlus(
        const MWVector<MWMatrix<MWData> > &v, 
        const MWMatrix<MWData> &m,
        MWVector<MWMatrix<MWData> > &ret);
    inline static MWVector<MWMatrix<MWData> > &AssignTimes(
        const MWVector<MWMatrix<MWData> > &v, 
        const MWMatrix<MWData> &m,
        MWVector<MWMatrix<MWData> > &ret);
    inline static MWVector<MWMatrix<MWData> > &AssignDiagonaledTimesTransformed(
        const MWVector<MWMatrix<MWData> > &v, 
        const MWMatrix<MWData> &m,
        MWVector<MWMatrix<MWData> > &ret);

    inline static MWVector<MWMatrix<MWData> > &AssignTimes(
        const MWVector<MWMatrix<MWData> > &v, 
        const MWData &scale,
        MWVector<MWMatrix<MWData> > &ret);

    inline static MWVector<MWMatrix<MWData> > &AssignTimes(
        const MWMatrix<MWData> &m,
        const MWVector<MWMatrix<MWData> > &v,
        MWVector<MWMatrix<MWData> > &ret);

    inline static MWVector<MWMatrix<MWData> > &AssignSquare(
        const MWVector<MWMatrix<MWData> > &v, 
        MWVector<MWMatrix<MWData> > &ret);
    inline static MWVector<MWMatrix<MWData> > &Assign(
        const MWVector<MWMatrix<MWData> > &v,
        MWVector<MWMatrix<MWData> > &ret);

    inline static MWMatrix<MWData> &AssignSum(
        const MWVector<MWMatrix<MWData> > &v,
        MWMatrix<MWData> &ret);
};

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignPlus(
    const MWVector<MWMatrix<MWData> > &v1, 
    const MWVector<MWMatrix<MWData> > &v2,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignPlus222;
    _vector_matrix_pt_1 = &v1;
    _vector_matrix_pt_2 = &v2;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignMinus(
    const MWVector<MWMatrix<MWData> > &v1, 
    const MWVector<MWMatrix<MWData> > &v2,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignMinus222;
    _vector_matrix_pt_1 = &v1;
    _vector_matrix_pt_2 = &v2;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignTimes(
    const MWVector<MWMatrix<MWData> > &v1, 
    const MWVector<MWMatrix<MWData> > &v2,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignTimes222;
    _vector_matrix_pt_1 = &v1;
    _vector_matrix_pt_2 = &v2;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignTimesTransformed(
    const MWVector<MWMatrix<MWData> > &v1, 
    const MWVector<MWMatrix<MWData> > &v2,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignTimesTransFormed222;
    _vector_matrix_pt_1 = &v1;
    _vector_matrix_pt_2 = &v2;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignDiagonaledTimesTransformed(
    const MWVector<MWMatrix<MWData> > &v1, 
    const MWVector<MWMatrix<MWData> > &v2,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignDiagonaledTimesTransformed222;
    _vector_matrix_pt_1 = &v1;
    _vector_matrix_pt_2 = &v2;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignDiagonaledTimes(
    const MWVector<MWMatrix<MWData> > &v1, 
    const MWVector<MWMatrix<MWData> > &v2,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignDiagonaledTimes222;
    _vector_matrix_pt_1 = &v1;
    _vector_matrix_pt_2 = &v2;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignPlus(
    const MWVector<MWMatrix<MWData> > &v, 
    const MWMatrix<MWData> &m,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignPlus221;
    _vector_matrix_pt_1 = &v;
    _matrix_pt_1 = &m;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignTimes(
    const MWVector<MWMatrix<MWData> > &v, 
    const MWMatrix<MWData> &m,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignTimes221;
    _vector_matrix_pt_1 = &v;
    _matrix_pt_1 = &m;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignDiagonaledTimesTransformed(
    const MWVector<MWMatrix<MWData> > &v, 
    const MWMatrix<MWData> &m,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignDiagonaledTimes221;
    _vector_matrix_pt_1 = &v;
    _matrix_pt_1 = &m;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignTimes(
    const MWVector<MWMatrix<MWData> > &v, 
    const MWData &scale,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignTimes220;
    _vector_matrix_pt_1 = &v;
    _data_pt_1 = &scale;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignTimes(
    const MWMatrix<MWData> &m, 
    const MWVector<MWMatrix<MWData> > &v,
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignTimes212;
    _matrix_pt_1 = &m;
    _vector_matrix_pt_1 = &v;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::AssignSquare(
    const MWVector<MWMatrix<MWData> > &v, 
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssignSquare22;
    _vector_matrix_pt_1 = &v;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWVector<MWMatrix<MWData> > &VectorMatrixMultiThreadCalculator::Assign(
    const MWVector<MWMatrix<MWData> > &v, 
    MWVector<MWMatrix<MWData> > &ret) {
    _function = VectorMatrixMultiThreadCalculatorFunctionAssign22;
    _vector_matrix_pt_1 = &v;
    _ret_pt = &ret;
    return AssignOperateMultiThread();
}

inline MWMatrix<MWData> &VectorMatrixMultiThreadCalculator::AssignSum(
    const MWVector<MWMatrix<MWData> > &v, 
    MWMatrix<MWData> &ret) {
    MWVector<MWMatrix<MWData> > mid_ret(_thread_id_vector.size(), ret);

    _function = VectorMatrixMultiThreadCalculatorFunctionAssignSum22;
    _vector_matrix_pt_1 = &v;
    _ret_pt = &mid_ret;
    AssignOperateMultiThread();

    return ::AssignSum(mid_ret, ret);
}
