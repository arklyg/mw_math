#ifndef _MW_VECTOR_H_
#define _MW_VECTOR_H_

#include <vector>
#include <list>

#include <mwglobal.h>
#include <mwlogger.h>

#include <mwserializable.h>
#include <typehelpers.h>

using namespace std;

template <typename T>
class MWVector : public MWCommonVector<T>, public MWSerializable
{
protected:
	size_t _len_for_serializing;

protected:
	virtual void add_serializing_sequence();
	virtual void add_serializing_sequence_for_instantiating();

public:
	MWVector();
	MWVector(const MWVector<T> &v);
	MWVector(const MWCommonList<T> &v);
	MWVector(size_t num, const T &val = T());
	MWVector(size_t num, const T* array);
	~MWVector();
	const MWVector<T> operator +(const MWVector<T> &v) const;
	const MWVector<T> operator +(const T &item) const;
	const MWVector<T> operator +=(const MWVector<T> &v);
	const MWVector<T> operator -(const MWVector<T> &v) const;
	const MWVector<T> operator -() const;
	const MWVector<T> operator -=(const MWVector<T> &v);
	const MWVector<T> operator *(const T &scale) const;
	const MWVector<T> operator *(const MWVector<T> &v) const;
	const MWVector<T> operator /(const T &sclae) const;
	const MWVector<T> t() const;
	const MWVector<T> &revert();
	const MWVector<T> &concat(const MWVector<T> &v);
	const T* to_array(T* array) const;
	const MWVector<T> &qsort();

	virtual size_t get_instantiated(const vector<char> &char_vector, size_t off);
};

template <typename T>
std::ostream & operator <<(std::ostream &os, const MWVector<T> &v)
{
	os << "{";
	for (size_t i = 0; i < v.size(); ++ i)
	{
		os << v[i];
		if (i + 1 < v.size())
		{
			os << ", ";
		}
	}
	os << "}";

	return os;
}

template <typename T>
int compare_t(const void* a, const void* b)
{
	return (* ((T*) a)) < (* ((T*) b)) ? -1 : ((* ((T*) a)) > (* ((T*) b)) ? 1 : 0);
}

template <typename T>
MWVector<T>::MWVector()
	: MWCommonVector<T>()
{
}

template <typename T>
MWVector<T>::MWVector(const MWVector<T> &v)
	: MWCommonVector<T>(v)
{
}

template <typename T>
MWVector<T>::MWVector(const MWCommonList<T> &v)
	: MWCommonVector<T>(v.size())
{
	size_t i = 0;
	for (typename MWCommonList<T>::const_iterator iter = v.begin(); iter != v.end(); ++ iter)
	{
		(* this)[i ++] = * iter;
	}
}

template <typename T>
MWVector<T>::MWVector(size_t num, const T &val)
	: MWCommonVector<T>(num, val)
{
}

template <typename T>
MWVector<T>::MWVector(size_t num, const T* array)
	: MWCommonVector<T>(num)
{
	for (size_t i = 0; i < num; ++ i)
	{
		(* this)[i] = array[i];
	}
}

template <typename T>
MWVector<T>::~MWVector()
{
}

template <typename T>
const MWVector<T> MWVector<T>::operator +(const MWVector<T> &v) const
{
	MWVector<T> ret(v.size());
	if (this->size() != v.size())
	{
		LOG_DEBUG(_logger, "[this->size() = " << this->size() << "] != [v.size() = " << v.size() << "], can not do operator +");
		return ret;
	}

	for (size_t i = 0; i < this->size(); ++ i)
	{
		ret[i] = (*this)[i] + v[i];
	}

	return ret;
}

template <typename T>
const MWVector<T> MWVector<T>::operator +(const T &item) const
{
	MWVector<T> ret(this->size());

	for (size_t i = 0; i < this->size(); ++ i)
	{
		ret[i] = (*this)[i] + item;
	}

	return ret;
}

template <typename T>
const MWVector<T> MWVector<T>::operator +=(const MWVector<T> &v)
{
	if (this->size() != v.size())
	{
		LOG_DEBUG(_logger, "[this+>size() = " << this->size() << "] != [v.size() = " << v.size() << "], can not do operator +=");
		return *this;
	}

	for (size_t i = 0; i < this->size(); ++ i)
	{
		(*this)[i] += v[i];
	}

	return *this;
}

template <typename T>
const MWVector<T> MWVector<T>::operator -(const MWVector<T> &v) const
{
	MWVector<T> ret(v.size());
	if (this->size() != v.size())
	{
		LOG_ERROR(_logger, "[this->size() = " << this->size() << "] != [v.size() = " << v.size() << "], can not do operator -");
		return ret;
	}

	for (size_t i = 0; i < this->size(); ++ i)
	{
		ret[i] = (*this)[i] - v[i];
	}

	return ret;
}

template <typename T>
const MWVector<T> MWVector<T>::operator -() const
{
	MWVector<T> ret(this->size());
	for (size_t i = 0; i < this->size(); ++ i)
	{
		ret[i] = - (*this)[i];
	}

	return ret;
}

template <typename T>
const MWVector<T> MWVector<T>::operator -=(const MWVector<T> &v)
{
	if (this->size() != v.size())
	{
		LOG_DEBUG(_logger, "[this->size() = " << this->size() << "] != [v.size() = " << v.size() << "], can not do operator -=");
		return *this;
	}

	for (size_t i = 0; i < this->size(); ++ i)
	{
		(*this)[i] -= v[i];
	}

	return *this;
}

template <typename T>
const MWVector<T> MWVector<T>::operator *(const MWVector<T> &v) const
{
	MWVector<T> ret(v.size());
	if (this->size() != v.size())
	{
		LOG_ERROR(_logger, "[this->size() = " << this->size() << "] != [v.size() = " << v.size() << "], can not do operator *");
		return ret;
	}

	for (size_t i = 0; i < this->size(); ++ i)
	{
		ret[i] = (*this)[i] * v[i];
	}

	return ret;
}

template <typename T>
const MWVector<T> MWVector<T>::operator *(const T &scale) const
{
	MWVector<T> ret(this->size());
	for (size_t i = 0; i < this->size(); ++ i)
	{
		ret[i] = (*this)[i] * scale;
	}

	return ret;
}

template <typename T>
const MWVector<T> MWVector<T>::operator /(const T &scale) const
{
	MWVector<T> ret(this->size());
	for (size_t i = 0; i < this->size(); ++ i)
	{
		ret[i] = (*this)[i] / scale;
	}

	return ret;
}

template <typename T>
const MWVector<T> MWVector<T>::t() const
{
	MWVector<T> ret(this->size());
	for (size_t i = 0; i < this->size(); ++ i)
	{
		ret[i] = ((*this)[i]).t();
	}

	return ret;
}

template <typename T>
const MWVector<T> &MWVector<T>::revert()
{
	if (this->size() > 1)
	{
		T item;
		for (size_t i = 0; i < this->size() - i - 1; ++ i)
		{
			item = (*this)[i];
			(*this)[i] = (*this)[this->size() - i - 1];
			(*this)[this->size() - i - 1] = item;
		}
	}

	return *this;
}

template <typename T>
void MWVector<T>::add_serializing_sequence()
{
	_len_for_serializing = this->size();
	add_serializing_sequence_data(& _len_for_serializing);
	if (this->empty())
	{
		return;
	}

	for (size_t i = 0; i < _len_for_serializing; ++ i)
	{
		add_serializing_sequence_data(& ((* this)[i]));
	}
}

template <typename T>
void MWVector<T>::add_serializing_sequence_for_instantiating()
{
	add_serializing_sequence_data(& _len_for_serializing);
	T t;
	add_serializing_sequence_data(& t);
}

template <typename T>
size_t MWVector<T>::get_instantiated(const vector<char> &char_vector, size_t off)
{
	set_serializing_sequence_for_instantiating();

	size_t len;
	const size_t original_off = off;
	off += (this->*(_get_instantiated_function_vector[0]))(& len, char_vector, off);

	(* this) = MWVector<T>(len);
	for (size_t i = 0; i < len; ++ i)
	{
		off += (this->*(_get_instantiated_function_vector[1]))(& (* this)[i], char_vector, off);
	}

	return off - original_off;
}

template <typename T>
const MWVector<T> &MWVector<T>::concat(const MWVector<T> &v)
{
	for (size_t i = 0; i < v.size(); ++ i)
	{
		this->push_back(v[i]);
	}

	return *this;
}

template <typename T>
const T* MWVector<T>::to_array(T* array) const
{
	for (size_t i = 0; i < this->size(); ++ i)
	{
		array[i] = (* this)[i];
	}

	return array;
}

template <typename T>
const MWVector<T> &MWVector<T>::qsort()
{
	if (this->empty())
	{
		return * this;
	}

	T base[this->size()];
	this->to_array(base);
	LOG_DEBUG(_logger, "before qsort, * this = " << (* this));
	
	::qsort(base, this->size(), sizeof(T), &compare_t<T>);
	* this = MWVector<T>(this->size(), base);
	LOG_DEBUG(_logger, "after qsort, * this = " << (* this));
	return * this;
}

#endif
