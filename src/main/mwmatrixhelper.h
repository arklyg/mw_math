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
MWVector<MWVector<MWMatrix<MWData> > > &assign_times_transformed(const MWVector<MWVector<MWMatrix<MWData> > > &v_m1, const MWVector<MWVector<MWMatrix<MWData> > > &v_m2, MWVector<MWVector<MWMatrix<MWData> > > &ret);


// function type: 2 * *
// function type: 2 2 2
MWVector<MWMatrix<MWData> > &assign_plus(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);
MWVector<MWMatrix<MWData> > &assign_minus(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);
MWVector<MWMatrix<MWData> > &assign_times(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);
MWVector<MWMatrix<MWData> > &assign_times_transformed(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);
MWVector<MWMatrix<MWData> > &assign_diagonaled_times_transformed(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);
MWVector<MWMatrix<MWData> > &assign_diagonaled_times(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);

// function type: 2 2 1
MWVector<MWMatrix<MWData> > &assign_plus(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);
MWVector<MWMatrix<MWData> > &assign_times(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);
MWVector<MWMatrix<MWData> > &assign_diagonaled_times_transformed(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &scale, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);

// function type: 2 2 0
MWVector<MWMatrix<MWData> > &assign_times(const MWVector<MWMatrix<MWData> > &v, const MWData &scale, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);

// function type: 2 1 2
MWVector<MWMatrix<MWData> > &assign_times(const MWMatrix<MWData> &m, const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);

// function type: 2 2
MWVector<MWMatrix<MWData> > &assign_square(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);
MWVector<MWMatrix<MWData> > &assign(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0);

// function type: 1 * *
// function type: 1 1 1
MWMatrix<MWData> &assign_plus(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret);
MWMatrix<MWData> &assign_minus(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret);
MWMatrix<MWData> &assign_times(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret);
MWMatrix<MWData> &assign_times_transformed(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret);
MWMatrix<MWData> &assign_diagonaled_times_transformed(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret);
MWMatrix<MWData> &assign_diagonaled_times(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret);

// function type: 1 1 0
MWMatrix<MWData> &assign_times(const MWMatrix<MWData> &m, const MWData &scale, MWMatrix<MWData> &ret);

// function type: 1 2
MWMatrix<MWData> &assign_sum(const MWVector<MWMatrix<MWData> > &v, MWMatrix<MWData> &ret, size_t off = 0, size_t len = 0);

#endif
