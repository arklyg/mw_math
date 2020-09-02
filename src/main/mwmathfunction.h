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


#ifndef _MW_MATH_FUNCTION_H_
#define _MW_MATH_FUNCTION_H_

#include <math.h>

#include <mwsingleton.h>
#include <proclockable.h>
#include <mwserializablesingleton.h>

#include "mwmatrix.h"

enum MWMathFunctionType {
    MWMathFunctionTypeDerivable,
    MWMathFunctionTypeUnderivable
};

class MWMathFunction;

typedef MWMatrix<MWData> &(MWMathFunction::*
                           MWMathFunctionFunctionHandleAssignMatrixWithMatrix)(const MWMatrix<MWData> &,
                                                                               MWMatrix<MWData> &) const;
typedef MWMatrix<MWData> (MWMathFunction::*
                          MWMathFunctionFunctionHandleGetMatrixWithMatrix)(const MWMatrix<MWData> &)
const;
typedef MWVector<MWData> &(MWMathFunction::*
                           MWMathFunctionFunctionHandleAssignVectorWithVector)(const MWVector<MWData> &,
                                                                               MWVector<MWData> &) const;
typedef MWVector<MWData> (MWMathFunction::*
                          MWMathFunctionFunctionHandleGetVectorWithVector)(const MWVector<MWData> &)
const;

class MWMathFunction : public MWSerializableSingleton {
  protected:
    static pthread_cond_t _begin_cond;
    static pthread_cond_t _end_cond;
    static ProcLockable _begin_lock;
    static ProcLockable _end_lock;
    static std::vector<pthread_t> _thread_id_vector;
    static std::vector<size_t> _worker_id_vector;
    static std::vector<bool> _work_signal;

    static size_t _finished_count;
    static const MWMathFunction *_work_instance;
    static MWMathFunctionFunctionHandleAssignMatrixWithMatrix
    _AssignValueMatrix_function_pt;
    static const MWVector<MWMatrix<MWData> > *_input_pt;
    static MWVector<MWMatrix<MWData> > *_ret_pt;

    static bool _is_exit;

  protected:
    MWMatrix<MWData> &AssignMultiResult(const MWMatrix<MWData> &input,
                                          const MWMathFunctionFunctionHandleAssignVectorWithVector function_handle,
                                          MWMatrix<MWData> &ret) const;
    MWMatrix<MWData> GetMultiResult(const MWMatrix<MWData> &input,
                                    const MWMathFunctionFunctionHandleGetVectorWithVector function_handle) const;
    MWVector<MWMatrix<MWData> > &AssignMultiResult(const
                                                   MWVector<MWMatrix<MWData> > &input,
                                                   const MWMathFunctionFunctionHandleAssignMatrixWithMatrix function_handle,
                                                   MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0) const;
    MWVector<MWMatrix<MWData> > GetMultiResult(const MWVector<MWMatrix<MWData> >
                                               &input, const MWMathFunctionFunctionHandleGetMatrixWithMatrix function_handle)
    const;

    MWVector<MWMatrix<MWData> > &AssignValueVectorMatrixMultiThreadOperation(
        const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret,
        MWMathFunctionFunctionHandleAssignMatrixWithMatrix
        AssignValueMatrix_function_pt) const;

  public:
    static void Initialize(size_t thread_num);
    static void Finalize();

    static void *Run(void *arg);

    virtual ~MWMathFunction();

    MWVector<MWData> GetValue(const MWVector<MWData> &input) const;

    MWMatrix<MWData> GetValueMatrixStructure(const MWMatrix<MWData> &input)
    const;
    MWMatrix<MWData> &AssignValueMatrix(const MWMatrix<MWData> &input,
                                          MWMatrix<MWData> &ret) const;
    MWMatrix<MWData> GetValueMatrix(const MWMatrix<MWData> &input) const;

    MWVector<MWMatrix<MWData> > GetValueVectorMatrixStructure(
        const MWVector<MWMatrix<MWData> > &input) const;
    MWVector<MWMatrix<MWData> > &AssignValueVectorMatrix(
        const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret,
        size_t off = 0, size_t len = 0) const;
    MWVector<MWMatrix<MWData> > &AssignValueVectorMatrixMultiThread(
        const MWVector<MWMatrix<MWData> > &input,
        MWVector<MWMatrix<MWData> > &ret) const;
    MWVector<MWMatrix<MWData> > GetValueVectorMatrix(const
                                                     MWVector<MWMatrix<MWData> > &input) const;

    virtual MWVector<MWData> GetValueStructure(const MWVector<MWData> &input) const = 0;
    virtual MWVector<MWData> &AssignValue(const MWVector<MWData> &input,
                                           MWVector<MWData> &ret) const = 0;

    virtual MWMathFunctionType GetType() const = 0;
};

#endif
