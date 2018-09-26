#ifndef _MW_MATRIX_H_
#define _MW_MATRIX_H_

#include <mwglobal.h>
#include <mwlogger.h>

#include <mwserializable.h>

#include "mwmathglobal.h"
#include "mwvector.h"
#include "mwmatrixinfo.h"

using namespace std;

enum MWVectorAsMatrixType
{
	MWVectorAsMatrixTypeRow,
	MWVectorAsMatrixTypeColumn,
	MWVectorAsMatrixTypeDiagonal
};

template <typename T>
class MWMatrix : public MWSerializable
{
public:
	MWVector<MWVector<T> > _data;

private:
	void init();

public:
	MWMatrix();
	~MWMatrix();
	MWMatrix(size_t row_num, size_t column_num, T val = 0);
	MWMatrix(const MWMatrixInfo &info, T val = 0);
	MWMatrix(const MWVector<T> &vector, MWVectorAsMatrixType vector_type);
	MWMatrix(const MWVector<T> &diagonal);
	MWMatrix(const MWVector<MWMatrix<T> > &vector_matrix);

	MWMatrixInfo get_matrix_info() const;
	size_t get_row_num() const;
	size_t get_column_num() const;

	MWVector<T> &operator [](size_t i);
	const MWVector<T> &operator [](size_t i) const;

	const MWMatrix<T> &operator =(const MWMatrix<T> &m);
	const MWMatrix<T> &operator =(const T &element);
	const MWMatrix<T> operator +(const MWMatrix<T> &m) const;
	const MWMatrix<T> operator +(const MWVector<MWMatrix<T> > &v_m) const;
	const MWMatrix<T> operator +=(const MWMatrix<T> &m);
	const MWMatrix<T> operator -(const MWMatrix<T> &m) const;
	const MWMatrix<T> operator -=(const MWMatrix<T> &m);
	const MWMatrix<T> operator -() const;
	const MWMatrix<T> operator *(const MWMatrix<T> &m) const;
	const MWMatrix<T> operator *(const T &scale) const;
	const MWVector<MWMatrix<T> > operator *(const MWVector<MWMatrix<T> > &v_m) const;
	const MWMatrix<T> operator /(const T &scale) const;
	const MWMatrix<T> t() const;
	const MWMatrix<T> square() const;
	const MWMatrix<T> assign_square(MWMatrix<T> &ret) const;
	const MWMatrix<T> assign(MWMatrix<T> &ret) const;

	void add_row(const MWVector<T> &row);
	void add_column(const MWVector<T> &column);
	MWMatrix<T> get_row_as_matrix(size_t row_index, MWVectorAsMatrixType type) const;
	MWMatrix<T> get_column_as_matrix(size_t column_index, MWVectorAsMatrixType type) const;
	MWVector<T> get_row_as_vector(size_t row_index) const;
	MWVector<T> get_column_as_vector(size_t column_index) const;
	MWMatrix<T> get_row_average() const;
	MWMatrix<T> get_column_average() const;

	bool is_empty();

	virtual void add_serializing_sequence();
};

template <typename T>
std::ostream & operator <<(std::ostream &os, const MWMatrix<T> &m)
{
	os << "[";
	for (size_t i = 0, j; i < m.get_row_num(); ++ i)
	{
		os << "(";
		for (j = 0; j < m.get_column_num(); ++ j)
		{
			os << m._data[i][j];
			if (j + 1 < m.get_column_num())
			{
				os << ", ";
			}
		}
		os << ")";
		if (i + 1 < m.get_row_num())
		{
			os << ", ";
		}
	}
	os << "]";

	return os;
}

template <typename T>
const MWVector<MWMatrix<T> > operator *(const MWVector<MWMatrix<T> > &v_m, const T &scale)
{
	MWVector<MWMatrix<T> > ret(v_m.size());
	for (size_t i = 0; i < v_m.size(); ++ i)
	{
		ret[i] = v_m[i] * scale;
	}

	return ret;
}

template <typename T>
bool operator <(const MWMatrix<T> &m1, const MWMatrix<T> &m2)
{
	return m1._data < m2._data;
}

template <typename T>
bool operator >(const MWMatrix<T> &m1, const MWMatrix<T> &m2)
{
	return m1._data > m2._data;
}

template <typename T>
bool operator ==(const MWMatrix<T> &m1, const MWMatrix<T> &m2)
{
	return m1._data == m2._data;
}

template <typename T>
bool operator !=(const MWMatrix<T> &m1, const MWMatrix<T> &m2)
{
	return m1._data != m2._data;
}

template <typename T>
bool operator <=(const MWMatrix<T> &m1, const MWMatrix<T> &m2)
{
	return m1._data <= m2._data;
}

template <typename T>
bool operator >=(const MWMatrix<T> &m1, const MWMatrix<T> &m2)
{
	return m1._data >= m2._data;
}

template <typename T>
MWMatrix<T>::MWMatrix()
{
}

template <typename T>
MWMatrix<T>::~MWMatrix()
{
}

template <typename T>
MWMatrix<T>::MWMatrix(size_t row_num, size_t column_num, T val)
	: _data(row_num, MWVector<T>(column_num, val))
{
}

template <typename T>
MWMatrix<T>::MWMatrix(const MWMatrixInfo &info, T val)
	: _data(info._row_num, MWVector<T>(info._column_num, val))
{
}

template <typename T>
MWMatrix<T>::MWMatrix(const MWVector<T> &v, MWVectorAsMatrixType v_type)
{
	if (v_type == MWVectorAsMatrixTypeRow)
	{
		_data.push_back(v);
	}
	else if (v_type == MWVectorAsMatrixTypeColumn)
	{
		for (size_t i = 0; i < v.size(); ++ i)
		{
			_data.push_back(MWVector<T>(1, v[i]));
		}
	}
	else if (v_type == MWVectorAsMatrixTypeDiagonal)
	{
		_data = MWVector<MWVector<T> >(v.size(), MWVector<T>(v.size(), T(0)));
		for (size_t i = 0; i < v.size(); ++i)
		{
			_data[i][i] = v[i];
		}
	}
}

template <typename T>
MWMatrix<T>::MWMatrix(const MWVector<T> &diagonal)
	: _data(diagonal.size(), MWVector<T>(diagonal.size(), T(0)))
{
	for (size_t i = 0; i < diagonal.size(); ++ i)
	{
		_data[i][i] = diagonal[i];
	}
}

template <typename T>
MWMatrix<T>::MWMatrix(const MWVector<MWMatrix<T> > &vector_matrix)
	: _data(vector_matrix[0].get_row_num(), MWVector<T>(vector_matrix[0].get_column_num() * vector_matrix.size()))
{
	size_t matrix_row_num = vector_matrix[0].get_row_num(), matrix_column_num = vector_matrix[0].get_column_num();
	for (size_t k = 0, i, j; k < vector_matrix.size(); ++ k)
	{
		if (matrix_row_num != vector_matrix[k].get_row_num() || matrix_column_num != vector_matrix[k].get_row_num())
		{
			LOG_ERROR(_logger, "(vector_matrix[0]._info = " << vector_matrix[0].get_matrix_info() << ") != (vector_matrix[" << k << "]._info = " << vector_matrix[k].get_matrix_info() << "), return");
			break;
		}

		for (i = 0; i < matrix_row_num; ++ i)
		{
			for (j = 0; j < matrix_column_num; ++ j)
			{
				_data[i][k * matrix_column_num + j] = vector_matrix[k]._data[i][j];
			}
		}
	}
}

template <typename T>
MWMatrixInfo MWMatrix<T>::get_matrix_info() const
{
	return MWMatrixInfo(get_row_num(), get_column_num());
}

template <typename T>
size_t MWMatrix<T>::get_row_num() const
{
	return _data.size();
}

template <typename T>
size_t MWMatrix<T>::get_column_num() const
{
	return _data.size() == 0 ? 0 : _data[0].size();
}

template <typename T>
MWVector<T> &MWMatrix<T>::operator [](size_t i)
{
	return _data[i];
}

template <typename T>
const MWVector<T> &MWMatrix<T>::operator [](size_t i) const
{
	return _data[i];
}

template <typename T>
const MWMatrix<T> &MWMatrix<T>::operator =(const MWMatrix<T> &m)
{
	_data = m._data;
	return * this;
}

template <typename T>
const MWMatrix<T> &MWMatrix<T>::operator =(const T &element)
{
	for (size_t i = 0; i < get_row_num(); ++ i)
	{
		for (size_t j = 0; j < get_column_num(); ++ j)
		{
			_data[i][j] = element;
		}
	}

	return * this;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::operator +(const MWMatrix<T> &m) const
{
	if (m.get_matrix_info() != get_matrix_info())
	{
		LOG_ERROR(_logger, "(this->_matrix_info = " << get_matrix_info() << ") != (m._matrix_info = " << m.get_matrix_info() << "), can not do operator +");
		return MWMatrix<T>();
	}

	MWMatrix<T> ret(get_matrix_info());

	for (size_t i = 0; i < get_row_num(); ++ i)
	{
		ret._data[i] = _data[i] + m._data[i];
	}

	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::operator +(const MWVector<MWMatrix<T> > &v_m) const
{
	MWVector<MWMatrix<T> > ret(*this);

	for (size_t i = 0; i < v_m.size(); ++ i)
	{
		ret[i] += v_m[i];
	}

	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::operator +=(const MWMatrix<T> &m)
{
	if (m.get_matrix_info() != get_matrix_info())
	{
		LOG_ERROR(_logger, "(this->_matrix_info = " << get_matrix_info() << ") != (m._matrix_info = " << m.get_matrix_info() << "), can not do operator +=");
		return *this;
	}

	for (size_t i = 0; i < get_row_num(); ++ i)
	{
		_data[i] += m._data[i];
	}

	return *this;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::operator -(const MWMatrix<T> &m) const
{
	if (m.get_matrix_info() != get_matrix_info())
	{
		LOG_ERROR(_logger, "(this->_matrix_info = " << get_matrix_info() << ") != (m._matrix_info = " << m.get_matrix_info() << "), can not do operator -");
		return MWMatrix<T>();
	}

	MWMatrix<T> ret(get_matrix_info());

	for (size_t i = 0; i < get_row_num(); ++ i)
	{
		ret._data[i] = _data[i] - m._data[i];
	}

	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::operator -=(const MWMatrix<T> &m)
{
	if (m.get_matrix_info() != get_matrix_info())
	{
		LOG_ERROR(_logger, "(this->_matrix_info = " << get_matrix_info() << ") != (m._matrix_info = " << m.get_matrix_info() << "), can not do operator -=");
		return *this;
	}

	for (size_t i = 0; i < get_row_num(); ++ i)
	{
		_data[i] -= m._data[i];
	}

	return *this;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::operator -() const
{
	MWMatrix<T> ret;
	ret._data = - _data;
	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::operator *(const MWMatrix<T> &m) const
{
	if (get_column_num() != m.get_row_num())
	{
		LOG_ERROR(_logger, "this->_matrix_info = " << get_matrix_info() << ", m._matrix_info = " << m.get_matrix_info() << ", can not do operator *");
		return MWMatrix<T>();
	}

	MWMatrix<T> ret(get_row_num(), m.get_column_num());

	for (size_t i_row = 0, i_column, i; i_row < get_row_num(); ++ i_row)
	{
		for (i_column = 0; i_column < m.get_column_num(); ++ i_column)
		{
			for (i = 0; i < get_column_num(); ++ i)
			{
				ret._data[i_row][i_column] += _data[i_row][i] * m._data[i][i_column];
			}
		}
	}

	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::operator *(const T &scale) const
{
	MWMatrix<T> ret(get_matrix_info());

	for (size_t i = 0; i < get_row_num(); ++ i)
	{
		ret._data[i] = _data[i] * scale;
	}

	return ret;
}

template <typename T>
const MWVector<MWMatrix<T> > MWMatrix<T>::operator *(const MWVector<MWMatrix<T> > &v_m) const
{
	MWVector<MWMatrix<T> > ret(v_m.size());

	for (size_t i = 0; i < v_m.size(); ++ i)
	{
		ret[i] = *this * v_m[i];
	}

	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::operator /(const T &scale) const
{
	MWMatrix<T> ret(get_matrix_info());

	for (size_t i = 0; i < get_row_num(); ++ i)
	{
		ret._data[i] = _data[i] / scale;
	}

	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::t() const
{
	MWMatrix<T> ret(get_column_num(), get_row_num());

	for (size_t i = 0, j; i < get_row_num(); ++ i)
	{
		for (j = 0; j < get_column_num(); ++ j)
		{
			ret._data[j][i] = _data[i][j];
		}
	}

	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::square() const
{
	MWMatrix<T> ret(get_matrix_info());
	for (size_t i = 0, j; i < get_row_num(); ++ i)
	{
		for (j = 0; j < get_column_num(); ++ j)
		{
			ret._data[i][j] = _data[i][j] * _data[i][j];
		}
	}

	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::assign_square(MWMatrix<T> &ret) const
{
	for (size_t i = 0, j; i < get_row_num(); ++ i)
	{
		for (j = 0; j < get_column_num(); ++ j)
		{
			ret._data[i][j] = _data[i][j] * _data[i][j];
		}
	}

	return ret;
}

template <typename T>
const MWMatrix<T> MWMatrix<T>::assign(MWMatrix<T> &ret) const
{
	for (size_t i = 0, j; i < get_row_num(); ++ i)
	{
		for (j = 0; j < get_column_num(); ++ j)
		{
			ret._data[i][j] = _data[i][j];
		}
	}

	return ret;
}

template <typename T>
void MWMatrix<T>::add_row(const MWVector<T> &row)
{
	if (!is_empty() && row.size() != get_column_num())
	{
		LOG_ERROR(_logger, "this matrix [size = (" << get_row_num() << " * " << get_column_num() << " )] can not add this vector [ size = " << row.size() << " ] as row");
		return;
	}

	_data.push_back(row);
}

template <typename T>
void MWMatrix<T>::add_column(const MWVector<T> &column)
{
	if (!is_empty() && column.size() != get_column_num())
	{
		LOG_ERROR(_logger, "this matrix [size = (" << get_row_num() << " * " << get_column_num() << " )] can not add this vector [ size = " << column.size() << " ] as column");
		return;
	}

	for (size_t i = 0; i < get_column_num(); ++ i)
	{
		_data[i].push_back(column[i]);
	}
}

template <typename T>
MWMatrix<T> MWMatrix<T>::get_row_as_matrix(size_t row_index, MWVectorAsMatrixType type) const
{
	if (row_index >= get_row_num())
	{
		LOG_ERROR(_logger, "( row_index = " << row_index << " ) >= ( this matrix row num = " << get_row_num() << " )");
		return MWMatrix<T>();
	}

	MWMatrix<T> ret(type == MWVectorAsMatrixTypeRow ? 1 : get_column_num(), type == MWVectorAsMatrixTypeRow ? get_column_num() : 1);
	for (size_t i = 0; i < get_column_num(); ++ i)
	{
		ret._data[type == MWVectorAsMatrixTypeRow ? 0 : i][type == MWVectorAsMatrixTypeRow ? i : 0] = _data[row_index][i];
	}

	return ret;
}

template <typename T>
MWMatrix<T> MWMatrix<T>::get_column_as_matrix(size_t column_index, MWVectorAsMatrixType type) const
{
	if (column_index >= get_column_num())
	{
		LOG_ERROR(_logger, "( column_index = " << column_index << " ) >= ( this matrix column num = " << get_column_num() << " )");
		return MWMatrix<T>();
	}

	MWMatrix<T> ret(type == MWVectorAsMatrixTypeColumn ? get_row_num() : 1, type == MWVectorAsMatrixTypeColumn ? 1 : get_row_num());
	for (size_t i = 0; i < get_row_num(); ++ i)
	{
		ret._data[type == MWVectorAsMatrixTypeColumn ? i : 0][type == MWVectorAsMatrixTypeColumn ? 0 : i] = _data[i][column_index];
	}

	return ret;
}

template <typename T>
MWVector<T> MWMatrix<T>::get_row_as_vector(size_t row_index) const
{
	if (row_index >= get_row_num())
	{
		LOG_ERROR(_logger, "row_index > this row num");
		return MWVector<T>();
	}

	return _data[row_index];
}

template <typename T>
MWVector<T> MWMatrix<T>::get_column_as_vector(size_t column_index) const
{
	if (column_index >= get_column_num())
	{
		LOG_ERROR(_logger, "column_index > this column num");
		return MWVector<T>();
	}

	MWVector<T> ret(get_row_num());
	for (size_t i = 0; i < get_row_num(); ++ i)
	{
		ret[i] = _data[i][column_index];
	}

	return ret;
}

template <typename T>
MWMatrix<T> MWMatrix<T>::get_row_average() const
{
	MWMatrix<T> ret(1, get_column_num());

	for (size_t i = 0, j; i < get_row_num(); ++ i)
	{
		for (j = 0; j < get_column_num(); ++ j)
		{
			ret._data[0][j] += _data[i][j];
		}
	}

	return ret / get_row_num();
}

template <typename T>
MWMatrix<T> MWMatrix<T>::get_column_average() const
{
	MWMatrix<T> ret(get_row_num(), 1);

	for (size_t i = 0, j; i < get_row_num(); ++ i)
	{
		for (j = 0; j < get_column_num(); ++ j)
		{
			ret._data[i][0] += _data[i][j];
		}
	}

	return ret / get_column_num();
}

template <typename T>
bool MWMatrix<T>::is_empty()
{
	return get_row_num() == 0 || get_column_num() == 0;
}

template <typename T>
void MWMatrix<T>::add_serializing_sequence()
{
	add_serializing_sequence_data(& _data);
}

#endif
