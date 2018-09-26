#include "classicnormalizefunction.h"

void ClassicNormalizeFunction::initialize(MWData amplify_arg)
{
	_amplify_arg = amplify_arg;
}

MWVector<MWData> ClassicNormalizeFunction::get_value_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(input.size());
}

MWVector<MWData> &ClassicNormalizeFunction::assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	MWData average(0);
	for (size_t i = 0; i < input.size(); ++ i)
	{
		average += input[i];
	}
	average = average / input.size();

	for (size_t i = 0; i < input.size(); ++ i)
	{
		ret[i] = (input[i] - average) * _amplify_arg / average;
	}
	
	return ret;
}
