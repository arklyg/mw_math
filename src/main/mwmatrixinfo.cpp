#include "mwmatrixinfo.h"

MWMatrixInfo::MWMatrixInfo(size_t row_num, size_t column_num)
	: _row_num(row_num)
	, _column_num(column_num)
{
}

bool MWMatrixInfo::operator ==(const MWMatrixInfo &info)
{
	return _row_num == info._row_num && _column_num == info._column_num;
}

bool MWMatrixInfo::operator !=(const MWMatrixInfo &info)
{
	return !(*this == info);
}

void MWMatrixInfo::add_serializing_sequence()
{
	add_serializing_sequence_data(& _row_num);
	add_serializing_sequence_data(& _column_num);
}

std::ostream & operator <<(std::ostream &os, const MWMatrixInfo &info)
{
	os << "(_row_num = " << info._row_num << ", _column_num = " << info._column_num << ")";

	return os;
}
