#ifndef _CLASSIC_NORMALIZE_FUNCTION_H_
#define _CLASSIC_NORMALIZE_FUNCTION_H_

#include <mwsingleton.h>

#include "mwunderivablemathfunction.h"

class ClassicNormalizeFunction;

class ClassicNormalizeFunction : public MWUnderivableMathFunction, public MWSingleton<ClassicNormalizeFunction>
{
private:
	MWData _amplify_arg;

public:
	void initialize(MWData amplify_arg);

	virtual MWVector<MWData> get_value_structure(const MWVector<MWData> &input) const;
	virtual MWVector<MWData> &assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const;
};

#endif
