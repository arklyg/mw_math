#include "randomfunction.h"

void RandomFunction::initialize(unsigned int* seedp)
{
	srand(seedp == NULL ? time(NULL) : * seedp);
}

MWVector<MWData> RandomFunction::get_value_structure(const MWVector<MWData> &input) const
{
	return MWVector<MWData>(1);
}

MWVector<MWData> &RandomFunction::assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	ret[0] = ((MWData) rand()) / RAND_MAX * (input[1] - input[0]) + input[0];
	return ret;
}
