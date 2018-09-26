#ifndef _FIXED_AREA_SIN_BY_COUNT_FUNCTION_H_
#define _FIXED_AREA_SIN_BY_COUNT_FUNCTION_H_

#include <mwsingleton.h>

#include "mwunderivablemathfunction.h"

class FixedAreaSinByCountFunction;

class FixedAreaSinByCountFunction : public MWUnderivableMathFunction, public MWSingleton<FixedAreaSinByCountFunction>
{
public:
	virtual MWVector<MWData> get_value_structure(const MWVector<MWData> &input) const;
	virtual MWVector<MWData> &assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const;
};

#endif
