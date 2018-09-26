#ifndef _ORDER_VALUE_FUNCTION_H_
#define _ORDER_VALUE_FUNCTION_H_

#include <mwsingleton.h>

#include "mwunderivablemathfunction.h"

class OrderValueFunction;

class OrderValueFunction : public MWUnderivableMathFunction, public MWSingleton<OrderValueFunction>
{
private:
	map<MWData, MWData> _value_map;
	MWData _min_value;
	MWData _max_value;

public:
	void initialize(const list<MWData> &data_list, MWData min_value, MWData max_value);
	void initialize(const MWVector<MWVector<MWMatrix<MWData> > > &data_vector_vector, MWData min_value, MWData max_value);

	virtual MWVector<MWData> get_value_structure(const MWVector<MWData> &input) const;
	virtual MWVector<MWData> &assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const;
	void assign_value(list<MWData> &data_list) const;
};

#endif
