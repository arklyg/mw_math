#ifndef _NORMALIZE_FUNCTION_H_
#define _NORMALIZE_FUNCTION_H_

#include <mwsingleton.h>

#include "mwunderivablemathfunction.h"

class NormalizeFunction;

class NormalizeFunction : public MWUnderivableMathFunction, public MWSingleton<NormalizeFunction>
{
public:
	virtual MWVector<MWData> get_value_structure(const MWVector<MWData> &input) const;
	virtual MWVector<MWData> &assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const;
};

#endif
