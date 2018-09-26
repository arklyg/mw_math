#ifndef _MW_DERIVABLE_MATH_FUNCTION_H_
#define _MW_DERIVABLE_MATH_FUNCTION_H_

#include "mwmathfunction.h"

#define MW_DERIVABLE_MATH_FUNCTION_LOGSIG 1
#define MW_DERIVABLE_MATH_FUNCTION_LINEAR 2

class MWDerivableMathFunction;

class MWDerivableMathFunction : public MWMathFunction
{
public:
	virtual ~MWDerivableMathFunction();

	MWVector<MWData> get_derivative(const MWVector<MWData> &input) const;

	MWMatrix<MWData> get_derivative_matrix_structure(const MWMatrix<MWData> &input) const;
	MWMatrix<MWData> &assign_derivative_matrix(const MWMatrix<MWData> &input, MWMatrix<MWData> &ret) const;
	MWMatrix<MWData> get_derivative_matrix(const MWMatrix<MWData> &input) const;

	MWVector<MWMatrix<MWData> > get_derivative_vector_matrix_structure(const MWVector<MWMatrix<MWData> > &input) const;
	MWVector<MWMatrix<MWData> > &assign_derivative_vector_matrix(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0) const;
	MWVector<MWMatrix<MWData> > &assign_derivative_vector_matrix_multi_thread(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret) const;
	MWVector<MWMatrix<MWData> > get_derivative_vector_matrix(const MWVector<MWMatrix<MWData> > &input) const;

	virtual MWMathFunctionType get_type() const;

	virtual MWVector<MWData> get_derivative_structure(const MWVector<MWData> &input) const = 0;
	virtual MWVector<MWData> &assign_derivative(const MWVector<MWData> &input, MWVector<MWData> &ret) const = 0;
};

#endif
