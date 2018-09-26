#include "logsigfunction.h"
#include "linearfunction.h"

#include "mwderivablemathfunction.h"

MWMathFunctionType MWDerivableMathFunction::get_type() const
{
	return MWMathFunctionTypeDerivable;
}

MWDerivableMathFunction::~MWDerivableMathFunction()
{
}

MWVector<MWData> MWDerivableMathFunction::get_derivative(const MWVector<MWData> &input) const
{
	MWVector<MWData> ret = get_derivative_structure(input);
	return assign_derivative(input, ret);
}

MWMatrix<MWData> MWDerivableMathFunction::get_derivative_matrix_structure(const MWMatrix<MWData> &input) const
{
	return get_multi_result(input, static_cast<MWMathFunctionFunctionHandleGetVectorWithVector>(& MWDerivableMathFunction::get_derivative_structure));
}

MWMatrix<MWData> &MWDerivableMathFunction::assign_derivative_matrix(const MWMatrix<MWData> &input, MWMatrix<MWData> &ret) const
{
	return assign_multi_result(input, static_cast<MWMathFunctionFunctionHandleAssignVectorWithVector>(& MWDerivableMathFunction::assign_derivative), ret);
}

MWMatrix<MWData> MWDerivableMathFunction::get_derivative_matrix(const MWMatrix<MWData> &input) const
{
	return get_multi_result(input, static_cast<MWMathFunctionFunctionHandleGetVectorWithVector>(& MWDerivableMathFunction::get_derivative));
}

MWVector<MWMatrix<MWData> > MWDerivableMathFunction::get_derivative_vector_matrix_structure(const MWVector<MWMatrix<MWData> > &input) const
{
	return get_multi_result(input, static_cast<MWMathFunctionFunctionHandleGetMatrixWithMatrix>(& MWDerivableMathFunction::get_derivative_matrix_structure));
}

MWVector<MWMatrix<MWData> > &MWDerivableMathFunction::assign_derivative_vector_matrix(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len) const
{
	return assign_multi_result(input, static_cast<MWMathFunctionFunctionHandleAssignMatrixWithMatrix>(& MWDerivableMathFunction::assign_derivative_matrix), ret, off, len);
}

MWVector<MWMatrix<MWData> > &MWDerivableMathFunction::assign_derivative_vector_matrix_multi_thread(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret) const
{
	return assign_value_vector_matrix_multi_thread_operation(input, ret, static_cast<MWMathFunctionFunctionHandleAssignMatrixWithMatrix>(& MWDerivableMathFunction::assign_derivative_matrix));
}

MWVector<MWMatrix<MWData> > MWDerivableMathFunction::get_derivative_vector_matrix(const MWVector<MWMatrix<MWData> > &input) const
{
	return get_multi_result(input, static_cast<MWMathFunctionFunctionHandleGetMatrixWithMatrix>(& MWDerivableMathFunction::get_derivative_matrix));
}
