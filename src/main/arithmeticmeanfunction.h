#ifndef _ARITHMETIC_MEAN_FUNCTION_H_
#define _ARITHMETIC_MEAN_FUNCTION_H_

#include <mwsingleton.h>

#include "mwunderivablemathfunction.h"

class ArithmeticMeanFunction;

class ArithmeticMeanFunction : public MWUnderivableMathFunction, public MWSingleton<ArithmeticMeanFunction>
{
public:
	virtual MWVector<MWData> get_value_structure(const MWVector<MWData> &input) const;
	virtual MWVector<MWData> &assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const;
};

#endif
