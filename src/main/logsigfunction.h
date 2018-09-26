#ifndef _LOGSIG_FUNCTION_H_
#define _LOGSIG_FUNCTION_H_

#include <mwsingleton.h>

#include "mwderivablemathfunction.h"

class LogsigFunction;

class LogsigFunction : public MWDerivableMathFunction, public MWSingleton<LogsigFunction>
{
public:
	virtual MWVector<MWData> get_value_structure(const MWVector<MWData> &input) const;
	virtual MWVector<MWData> &assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const;
	virtual MWVector<MWData> get_derivative_structure(const MWVector<MWData> &input) const;
	virtual MWVector<MWData> &assign_derivative(const MWVector<MWData> &input, MWVector<MWData> &ret) const;
};

#endif
