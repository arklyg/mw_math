#include "mwunderivablemathfunction.h"

MWUnderivableMathFunction::~MWUnderivableMathFunction()
{
}

MWMathFunctionType MWUnderivableMathFunction::get_type() const
{
	return MWMathFunctionTypeUnderivable;
}
