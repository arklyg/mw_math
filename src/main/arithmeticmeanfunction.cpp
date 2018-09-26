#include "arithmeticmeanfunction.h"

MWVector<MWData> ArithmeticMeanFunction::get_value_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(1);
}

MWVector<MWData> &ArithmeticMeanFunction::assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	ret[0] = 1 / input[1];
	return ret;
}
