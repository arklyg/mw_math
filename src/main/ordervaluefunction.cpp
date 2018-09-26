#include "ordervaluefunction.h"

#include <set>

void OrderValueFunction::initialize(const list<MWData> &data_list, MWData min_value, MWData max_value)
{
	_min_value = min_value;
	_max_value = max_value;

	if (data_list.empty()) {
		return;
	}

	size_t _count_eq(0), _count_gt(0), _count_ls(0);

	// 去重
	map<MWData, size_t> data_map;
	map<MWData, size_t>::iterator finder;
	for (list<MWData>::const_iterator data_iter(data_list.begin()); data_iter != data_list.end(); ++data_iter) {
		finder = data_map.find(*data_iter);
		if (finder == data_map.end()) {
			data_map.insert(pair<MWData, size_t>(*data_iter, 1));
		} else {
			++ (finder->second);
		}

		if (*data_iter > 0)	{
			++ _count_gt;
		} else if (*data_iter < 0) {
			++ _count_ls;
		} else {
			++ _count_eq;
		}
	}

	if (data_map.empty()) {
		return;
	}

	MWData unit_value_ls(_min_value / ((MWData) (_count_ls + _count_eq))), unit_value_gt(_max_value / ((MWData) (_count_gt + _count_eq)));

	size_t count(0);
	for (finder = data_map.begin(); finder != data_map.end() && finder->first < 0; ++ finder) {
		_value_map.insert(pair<MWData, MWData>(finder->first, _min_value - unit_value_ls * (((double) count) + ((double) finder->second) / 2)));
		count += finder->second;
	}

	if (finder == data_map.end()) {
		return;
	}

	count = 0;
	if (finder->first == 0) {
		_value_map.insert(pair<MWData, MWData>(0, 0));
		count += finder->second;
	}

	for (++ finder; finder != data_map.end(); ++ finder) {
		_value_map.insert(pair<MWData, MWData>(finder->first, unit_value_gt * (((double) count) + ((double) finder->second) / 2)));
		count += finder->second;
	}
}

void OrderValueFunction::initialize(const MWVector<MWVector<MWMatrix<MWData> > > &data_vector_vector, MWData min_value, MWData max_value)
{
	_min_value = min_value;
	_max_value = max_value;

	if (data_vector_vector.empty())
	{
		return;
	}

	size_t _count_eq(0), _count_gt(0), _count_ls(0);

	// 去重
	map<MWData, size_t> data_map;
	map<MWData, size_t>::iterator finder;
	for (size_t i = 0, j; i < data_vector_vector.size(); ++ i)
	{
		for (j = 0; j < data_vector_vector[i].size(); ++ j)
		{
			finder = data_map.find(data_vector_vector[i][j][0][0]);
			if (finder == data_map.end())
			{
				data_map.insert(pair<MWData, size_t>(data_vector_vector[i][j][0][0], 1));
			}
			else
			{
				++ (finder->second);
			}

			if (data_vector_vector[i][j][0][0] > 0)
			{
				++ _count_gt;
			}
			else if (data_vector_vector[i][j][0][0] < 0)
			{
				++ _count_ls;
			}
			else
			{
				++ _count_eq;
			}
		}
	}

	if (data_map.empty())
	{
		return;
	}

	MWData unit_value_ls(_min_value / ((MWData) (_count_ls + _count_eq))), unit_value_gt(_max_value / ((MWData) (_count_gt + _count_eq)));

	size_t count(0);
	for (finder = data_map.begin(); finder != data_map.end() && finder->first < 0; ++ finder)
	{
		_value_map.insert(pair<MWData, MWData>(finder->first, _min_value - unit_value_ls * (((double) count) + ((double) finder->second) / 2)));
		count += finder->second;
	}

	if (finder == data_map.end())
	{
		return;
	}

	count = 0;
	if (finder->first == 0)
	{
		_value_map.insert(pair<MWData, MWData>(0, 0));
		count += finder->second;
	}

	for (++ finder; finder != data_map.end(); ++ finder)
	{
		_value_map.insert(pair<MWData, MWData>(finder->first, unit_value_gt * (((double) count) + ((double) finder->second) / 2)));
		count += finder->second;
	}
}

MWVector<MWData> OrderValueFunction::get_value_structure(const MWVector<MWData> &input) const
{
	return input;
}

MWVector<MWData> &OrderValueFunction::assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const
{
	map<MWData, MWData>::const_iterator finder;
	for (size_t i = 0; i < input.size(); ++ i)
	{
		finder = _value_map.find(input[i]);
		ret[i] = finder == _value_map.end() ? 0 : finder->second;
		if (finder == _value_map.end())
		{
			LOG_WARN(_logger, "assign_value(" << input[i] << "), no such key, wrong call. but 0 returned");
		}
		LOG_TRACE(_logger, "before = " << input[i] << ", after = " << ret[i]);
	}

	return ret;
}

void OrderValueFunction::assign_value(list<MWData> &data_list) const {
	map<MWData, MWData>::const_iterator finder;
	for (list<MWData>::iterator data_iter(data_list.begin()); data_iter != data_list.end(); ++data_iter) {
		LOG_TRACE(_logger, "before = " << *data_iter);
		finder = _value_map.find(*data_iter);
		*data_iter = finder == _value_map.end() ? 0 : finder->second;
		if (finder == _value_map.end()) {
			LOG_WARN(_logger, "assign_value(" << *data_iter << "), no such key, wrong call. but 0 assigned");
		}
		LOG_TRACE(_logger, "after = " << *data_iter);
	}
}
