#ifndef _MW_MATRIX_INFO_H_
#define _MW_MATRIX_INFO_H_

#include <iostream>

#include <mwserializable.h>

class MWMatrixInfo : public MWSerializable
{
public:
	size_t _row_num;
	size_t _column_num;

public:
	MWMatrixInfo(size_t row_num = 0, size_t column_num = 0);

	bool operator ==(const MWMatrixInfo &info);
	bool operator !=(const MWMatrixInfo &info);

	virtual void add_serializing_sequence();
};

std::ostream & operator <<(std::ostream &os, const MWMatrixInfo &info);

#endif

