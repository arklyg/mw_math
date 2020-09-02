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


#ifndef _MW_DERIVABLE_MATH_FUNCTION_H_
#define _MW_DERIVABLE_MATH_FUNCTION_H_

#include "mwmathfunction.h"

#define MW_DERIVABLE_MATH_FUNCTION_LOGSIG 1
#define MW_DERIVABLE_MATH_FUNCTION_LINEAR 2

class MWDerivableMathFunction;

class MWDerivableMathFunction : public MWMathFunction {
  public:
    virtual ~MWDerivableMathFunction();

    MWVector<MWData> GetDerivative(const MWVector<MWData> &input) const;

    MWMatrix<MWData> GetDerivativeMatrixStructure(const MWMatrix<MWData> &input) const;
    MWMatrix<MWData> &AssignDerivativeMatrix(const MWMatrix<MWData> &input,
                                             MWMatrix<MWData> &ret) const;
    MWMatrix<MWData> GetDerivativeMatrix(const MWMatrix<MWData> &input) const;

    MWVector<MWMatrix<MWData> > GetDerivativeVectorMatrixStructure(
        const MWVector<MWMatrix<MWData> > &input) const;
    MWVector<MWMatrix<MWData> > &AssignDerivativeVectorMatrix(
        const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret,
        size_t off = 0, size_t len = 0) const;
    MWVector<MWMatrix<MWData> > &AssignDerivativeVectorMatrixMultiThread(
        const MWVector<MWMatrix<MWData> > &input,
        MWVector<MWMatrix<MWData> > &ret) const;
    MWVector<MWMatrix<MWData> > GetDerivativeVectorMatrix(
        const MWVector<MWMatrix<MWData> > &input) const;

    virtual MWMathFunctionType GetType() const;

    virtual MWVector<MWData> GetDerivativeStructure(const MWVector<MWData> &input)
    const = 0;
    virtual MWVector<MWData> &AssignDerivative(const MWVector<MWData> &input,
                                               MWVector<MWData> &ret) const = 0;
};

#endif
