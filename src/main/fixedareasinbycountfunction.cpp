#include "fixedareasinbycountfunction.h"

MWVector<MWData> FixedAreaSinByCountFunction::get_value_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(1);
}

MWVector<MWData> &FixedAreaSinByCountFunction::assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	ret[0] = cos(MW_MATH_CONSTANT_TWO_DIVIDES_PIE * input[0] / input[1]) - cos(MW_MATH_CONSTANT_TWO_DIVIDES_PIE * (input[0] + 1) / input[1]);
	return ret;
}
