#ifndef _FIXED_AREA_SIN_UP_BY_COUNT_FUNCTION_H_
#define _FIXED_AREA_SIN_UP_BY_COUNT_FUNCTION_H_

#include <mwsingleton.h>

#include "mwunderivablemathfunction.h"

class FixedAreaSinUpByCountFunction;

class FixedAreaSinUpByCountFunction : public MWUnderivableMathFunction, public MWSingleton<FixedAreaSinUpByCountFunction>
{
public:
	virtual MWVector<MWData> get_value_structure(const MWVector<MWData> &input) const;
	virtual MWVector<MWData> &assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const;
};

#endif
