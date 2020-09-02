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


#ifndef _MW_MATH_MATRIX_HELPER_H_
#define _MW_MATH_MATRIX_HELPER_H_

#include "mwmatrix.h"

/*
// function type meaning:
// the 1st digit stands for the amount of layers of the return value
// the 2nd digit stands for the amount of layers of the 1st argument
// the 3rd digit stands for the amount of layers of the 2nd argument
*/

// function type: 3 * *
// function type: 3 3 3
MWVector<MWVector<MWMatrix<MWData> > > &AssignTimesTransformed(
    const MWVector<MWVector<MWMatrix<MWData> > > &v_m1,
    const MWVector<MWVector<MWMatrix<MWData> > > &v_m2,
    MWVector<MWVector<MWMatrix<MWData> > > &ret);


// function type: 2 * *
// function type: 2 2 2
MWVector<MWMatrix<MWData> > &AssignPlus(const MWVector<MWMatrix<MWData> > &v1,
                                        const MWVector<MWMatrix<MWData> > &v2, 
                                        MWVector<MWMatrix<MWData> > &ret,
                                        size_t off = 0, 
                                        size_t len = 0);
MWVector<MWMatrix<MWData> > &AssignMinus(const MWVector<MWMatrix<MWData> > &v1,
                                         const MWVector<MWMatrix<MWData> > &v2, 
                                         MWVector<MWMatrix<MWData> > &ret,
                                         size_t off = 0, 
                                         size_t len = 0);
MWVector<MWMatrix<MWData> > &AssignTimes(const MWVector<MWMatrix<MWData> > &v1,
                                         const MWVector<MWMatrix<MWData> > &v2, 
                                         MWVector<MWMatrix<MWData> > &ret,
                                         size_t off = 0, 
                                         size_t len = 0);
MWVector<MWMatrix<MWData> > &AssignTimesTransformed(const MWVector<MWMatrix<MWData> > &v1, 
                                                    const MWVector<MWMatrix<MWData> > &v2,
                                                    MWVector<MWMatrix<MWData> > &ret, 
                                                    size_t off = 0, 
                                                    size_t len = 0);
MWVector<MWMatrix<MWData> > &AssignDiagonaledTimesTransformed(
                                                              const MWVector<MWMatrix<MWData> > &v1, 
                                                              const MWVector<MWMatrix<MWData> > &v2,
                                                              MWVector<MWMatrix<MWData> > &ret, 
                                                              size_t off = 0, 
                                                              size_t len = 0);
MWVector<MWMatrix<MWData> > &AssignDiagonaledTimes(const MWVector<MWMatrix<MWData> > &v1, 
                                                   const MWVector<MWMatrix<MWData> > &v2,
                                                   MWVector<MWMatrix<MWData> > &ret, 
                                                   size_t off = 0, 
                                                   size_t len = 0);

// function type: 2 2 1
MWVector<MWMatrix<MWData> > &AssignPlus(const MWVector<MWMatrix<MWData> > &v,
                                        const MWMatrix<MWData> &m, 
                                        MWVector<MWMatrix<MWData> > &ret, 
                                        size_t off = 0,
                                        size_t len = 0);
MWVector<MWMatrix<MWData> > &AssignTimes(const MWVector<MWMatrix<MWData> > &v,
                                         const MWMatrix<MWData> &m, 
                                         MWVector<MWMatrix<MWData> > &ret, 
                                         size_t off = 0,
                                         size_t len = 0);
MWVector<MWMatrix<MWData> > &AssignDiagonaledTimesTransformed(const MWVector<MWMatrix<MWData> > &v, 
                                                              const MWMatrix<MWData> &scale,
                                                              MWVector<MWMatrix<MWData> > &ret, 
                                                              size_t off = 0, 
                                                              size_t len = 0);

// function type: 2 2 0
MWVector<MWMatrix<MWData> > &AssignTimes(const MWVector<MWMatrix<MWData> > &v,
                                         const MWData &scale, 
                                         MWVector<MWMatrix<MWData> > &ret, 
                                         size_t off = 0,
                                         size_t len = 0);

// function type: 2 1 2
MWVector<MWMatrix<MWData> > &AssignTimes(const MWMatrix<MWData> &m,
                                         const MWVector<MWMatrix<MWData> > &v, 
                                         MWVector<MWMatrix<MWData> > &ret,
                                         size_t off = 0, 
                                         size_t len = 0);

// function type: 2 2
MWVector<MWMatrix<MWData> > &AssignSquare(const MWVector<MWMatrix<MWData> > &v,
                                           MWVector<MWMatrix<MWData> > &ret, 
                                           size_t off = 0, 
                                           size_t len = 0);
MWVector<MWMatrix<MWData> > &Assign(const MWVector<MWMatrix<MWData> > &v,
                                    MWVector<MWMatrix<MWData> > &ret, 
                                    size_t off = 0, 
                                    size_t len = 0);

// function type: 1 * *
// function type: 1 1 1
MWMatrix<MWData> &AssignPlus(const MWMatrix<MWData> &m1,
                             const MWMatrix<MWData> &m2, 
                             MWMatrix<MWData> &ret);
MWMatrix<MWData> &AssignMinus(const MWMatrix<MWData> &m1,
                              const MWMatrix<MWData> &m2, 
                              MWMatrix<MWData> &ret);
MWMatrix<MWData> &AssignTimes(const MWMatrix<MWData> &m1,
                              const MWMatrix<MWData> &m2, 
                              MWMatrix<MWData> &ret);
MWMatrix<MWData> &AssignTimesTransformed(const MWMatrix<MWData> &m1,
                                         const MWMatrix<MWData> &m2, 
                                         MWMatrix<MWData> &ret);
MWMatrix<MWData> &AssignDiagonaledTimesTransformed(const MWMatrix<MWData> &m1, 
                                                   const MWMatrix<MWData> &m2, 
                                                      MWMatrix<MWData> &ret);
MWMatrix<MWData> &AssignDiagonaledTimes(const MWMatrix<MWData> &m1,
                                        const MWMatrix<MWData> &m2, 
                                        MWMatrix<MWData> &ret);

// function type: 1 1 0
MWMatrix<MWData> &AssignTimes(const MWMatrix<MWData> &m, 
                              const MWData &scale,
                              MWMatrix<MWData> &ret);

// function type: 1 2
MWMatrix<MWData> &AssignSum(const MWVector<MWMatrix<MWData> > &v,
                            MWMatrix<MWData> &ret, 
                            size_t off = 0, 
                            size_t len = 0);

#endif
