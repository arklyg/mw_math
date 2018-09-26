#ifndef _MW_UNDERIVABLE_MATH_FUNCTION_H_
#define _MW_UNDERIVABLE_MATH_FUNCTION_H_

#include "mwmathfunction.h"

class MWUnderivableMathFunction : public MWMathFunction
{
public:
	virtual ~MWUnderivableMathFunction();

	virtual MWMathFunctionType get_type() const;
};

#endif

