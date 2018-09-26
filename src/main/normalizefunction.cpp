#include "normalizefunction.h"

MWVector<MWData> NormalizeFunction::get_value_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(1);
}

MWVector<MWData> &NormalizeFunction::assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	// MWData input = input[0], input_min = input[1], input_max = input[2], output_min = input[3], output_max = input[4];
	ret[0] = (input[0] - input[1]) / (input[2] - input[1]) * (input[4] - input[3]) + input[3];
	return ret;
}
