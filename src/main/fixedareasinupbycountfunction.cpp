#include "fixedareasinupbycountfunction.h"

MWVector<MWData> FixedAreaSinUpByCountFunction::get_value_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(1);
}

MWVector<MWData> &FixedAreaSinUpByCountFunction::assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	ret[0] = MW_MATH_CONSTANT_TWO_DIVIDES_PIE_DEVIDES_TOW_DEVIDES_PIE_MINUS_ONE * (1 / input[1] - MW_MATH_CONSTANT_PIE_DIVIDES_TWO * (sin(MW_MATH_CONSTANT_TWO_DIVIDES_PIE * (input[0] + 1) / input[1]) - sin(MW_MATH_CONSTANT_TWO_DIVIDES_PIE * input[0] / input[1])));
	return ret;
}
