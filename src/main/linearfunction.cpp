#include <math.h>

#include "mwmathglobal.h"

#include "linearfunction.h"

MWVector<MWData> LinearFunction::get_value_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(1);
}

MWVector<MWData> &LinearFunction::assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	ret[0] = input[0];
	return ret;
}

MWVector<MWData> LinearFunction::get_derivative_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(1);
}

MWVector<MWData> &LinearFunction::assign_derivative(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	ret[0] = 1;
	return ret;
}
