#include <math.h>

#include "mwmathglobal.h"

#include "logsigfunction.h"

MWVector<MWData> LogsigFunction::get_value_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(1);
}

MWVector<MWData> &LogsigFunction::assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	ret[0] = 1 / (1 + pow(MW_MATH_CONSTANT_E, - input[0]));
	return ret;
}

MWVector<MWData> LogsigFunction::get_derivative_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(1);
}

MWVector<MWData> &LogsigFunction::assign_derivative(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	assign_value(input, ret);
	ret[0] = (1 - ret[0]) * ret[0];
	return ret;
}
