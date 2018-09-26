#ifndef _RANDOM_FUNCTION_H_
#define _RANDOM_FUNCTION_H_

#include <mwsingleton.h>

#include "mwunderivablemathfunction.h"

class RandomFunction;

class RandomFunction : public MWUnderivableMathFunction, public MWSingleton<RandomFunction>
{
public:
	void initialize(unsigned int* seedp = NULL);

public:
	virtual MWVector<MWData> get_value_structure(const MWVector<MWData> &input) const;
	virtual MWVector<MWData> &assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const;
};

#endif

