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


#include "logsigfunction.h"
#include "linearfunction.h"

#include "mwderivablemathfunction.h"

MWMathFunctionType MWDerivableMathFunction::GetType() const {
    return MWMathFunctionTypeDerivable;
}

MWDerivableMathFunction::~MWDerivableMathFunction() {
}

MWVector<MWData> MWDerivableMathFunction::GetDerivative(
    const MWVector<MWData> &input) const {
    MWVector<MWData> ret = GetDerivativeStructure(input);
    return AssignDerivative(input, ret);
}

MWMatrix<MWData> MWDerivableMathFunction::GetDerivativeMatrixStructure(
    const MWMatrix<MWData> &input) const {
    return GetMultiResult(input,
                            static_cast<MWMathFunctionFunctionHandleGetVectorWithVector>
                            (&MWDerivableMathFunction::GetDerivativeStructure));
}

MWMatrix<MWData> &MWDerivableMathFunction::AssignDerivativeMatrix(
    const MWMatrix<MWData> &input, MWMatrix<MWData> &ret) const {
    return AssignMultiResult(input,
                               static_cast<MWMathFunctionFunctionHandleAssignVectorWithVector>
                               (&MWDerivableMathFunction::AssignDerivative), ret);
}

MWMatrix<MWData> MWDerivableMathFunction::GetDerivativeMatrix(
    const MWMatrix<MWData> &input) const {
    return GetMultiResult(input,
                            static_cast<MWMathFunctionFunctionHandleGetVectorWithVector>
                            (&MWDerivableMathFunction::GetDerivative));
}

MWVector<MWMatrix<MWData> >
MWDerivableMathFunction::GetDerivativeVectorMatrixStructure(
    const MWVector<MWMatrix<MWData> > &input) const {
    return GetMultiResult(input,
                          static_cast<MWMathFunctionFunctionHandleGetMatrixWithMatrix>
                          (&MWDerivableMathFunction::GetDerivativeMatrixStructure));
}

MWVector<MWMatrix<MWData> >
&MWDerivableMathFunction::AssignDerivativeVectorMatrix(
    const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret,
    size_t off, size_t len) const {
    return AssignMultiResult(input,
                             static_cast<MWMathFunctionFunctionHandleAssignMatrixWithMatrix>
                             (&MWDerivableMathFunction::AssignDerivativeMatrix), ret, off, len);
}

MWVector<MWMatrix<MWData> >
&MWDerivableMathFunction::AssignDerivativeVectorMatrixMultiThread(
    const MWVector<MWMatrix<MWData> > &input,
    MWVector<MWMatrix<MWData> > &ret) const {
    return AssignValueVectorMatrixMultiThreadOperation(input, ret,
        static_cast<MWMathFunctionFunctionHandleAssignMatrixWithMatrix>
        (&MWDerivableMathFunction::AssignDerivativeMatrix));
}

MWVector<MWMatrix<MWData> >
MWDerivableMathFunction::GetDerivativeVectorMatrix(
    const MWVector<MWMatrix<MWData> > &input) const {
    return GetMultiResult(input,
                          static_cast<MWMathFunctionFunctionHandleGetMatrixWithMatrix>
                          (&MWDerivableMathFunction::GetDerivativeMatrix));
}
