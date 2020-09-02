// Micro Wave Math
// Copyright (c) 2015-2020, Ark Lee
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You must obey the GNU General Public License in all respects for
// all of the code used.  If you modify file(s) with this exception, 
// you may extend this exception to your version of the file(s), but 
// you are not obligated to do so.  If you do not wish to do so, delete 
// this exception statement from your version. If you delete this exception 
// statement from all source files in the program, then also delete it here.
//
// Contact:  Ark Lee <arklee@houduan.online>
//           Beijing, China


#ifndef _MW_VECTOR_H_
#define _MW_VECTOR_H_

#include <vector>
#include <list>

#include <mwglobal.h>
#include <mwlogger.h>

#include <mwserializable.h>
#include <typehelpers.h>


template <typename TypeName>
class MWVector : public MWCommonVector<TypeName>, public MWSerializable {
  protected:
    size_t _len_for_serializing;

  protected:
    virtual void AddSequence();
    virtual void AddSequenceForDeserializing();

  public:
    MWVector();
    MWVector(const MWVector<TypeName> &v);
    MWVector(const MWCommonList<TypeName> &v);
    MWVector(size_t num, const TypeName &val = TypeName());
    MWVector(size_t num, const TypeName *array);
    ~MWVector();
    const MWVector<TypeName> operator +(const MWVector<TypeName> &v) const;
    const MWVector<TypeName> operator +(const TypeName &item) const;
    const MWVector<TypeName> operator +=(const MWVector<TypeName> &v);
    const MWVector<TypeName> operator -(const MWVector<TypeName> &v) const;
    const MWVector<TypeName> operator -() const;
    const MWVector<TypeName> operator -=(const MWVector<TypeName> &v);
    const MWVector<TypeName> operator *(const TypeName &scale) const;
    const MWVector<TypeName> operator *(const MWVector<TypeName> &v) const;
    const MWVector<TypeName> operator /(const TypeName &sclae) const;
    const MWVector<TypeName> T() const;
    const MWVector<TypeName> &Revert();
    const MWVector<TypeName> &Concat(const MWVector<TypeName> &v);
    const TypeName *ToArray(TypeName *array) const;
    const MWVector<TypeName> &Qsort();

    virtual size_t Deserialize(const std::vector<char> &char_vector, size_t off);
};

template <typename TypeName>
std::ostream &operator <<(std::ostream &os, const MWVector<TypeName> &v) {
    os << "{";
    for (size_t i = 0; i < v.size(); ++ i) {
        os << v[i];
        if (i + 1 < v.size()) {
            os << ", ";
        }
    }
    os << "}";

    return os;
}

template <typename TypeName>
int compare_t(const void *a, const void *b) {
    return (*((TypeName*) a)) < (*((TypeName*) b)) ? -1 : ((*((TypeName*) a)) > (*((TypeName*) b)) ? 1 : 0);
}

template <typename TypeName>
MWVector<TypeName>::MWVector()
    : MWCommonVector<TypeName>() {
}

template <typename TypeName>
MWVector<TypeName>::MWVector(const MWVector<TypeName> &v)
    : MWCommonVector<TypeName>(v) {
}

template <typename TypeName>
MWVector<TypeName>::MWVector(const MWCommonList<TypeName> &v)
    : MWCommonVector<TypeName>(v.size()) {
    size_t i = 0;
    for (typename MWCommonList<TypeName>::const_iterator iter = v.begin(); iter != v.end();
            ++ iter) {
        (*this)[i ++] = *iter;
    }
}

template <typename TypeName>
MWVector<TypeName>::MWVector(size_t num, const TypeName &val)
    : MWCommonVector<TypeName>(num, val) {
}

template <typename TypeName>
MWVector<TypeName>::MWVector(size_t num, const TypeName *array)
    : MWCommonVector<TypeName>(num) {
    for (size_t i = 0; i < num; ++ i) {
        (*this)[i] = array[i];
    }
}

template <typename TypeName>
MWVector<TypeName>::~MWVector() {
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::operator +(const MWVector<TypeName> &v) const {
    MWVector<TypeName> ret(v.size());
    if (this->size() != v.size()) {
        LOGDEBUG("[this->size() = " << this->size() << 
                 "] != [v.size() = " << v.size() << 
                 "], can not do operator +");
        return ret;
    }

    for (size_t i = 0; i < this->size(); ++ i) {
        ret[i] = (*this)[i] + v[i];
    }

    return ret;
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::operator +(const TypeName &item) const {
    MWVector<TypeName> ret(this->size());

    for (size_t i = 0; i < this->size(); ++ i) {
        ret[i] = (*this)[i] + item;
    }

    return ret;
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::operator +=(const MWVector<TypeName> &v) {
    if (this->size() != v.size()) {
        LOGDEBUG("[this+>size() = " << this->size() << 
                 "] != [v.size() = " << v.size() << 
                 "], can not do operator +=");
        return *this;
    }

    for (size_t i = 0; i < this->size(); ++ i) {
        (*this)[i] += v[i];
    }

    return *this;
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::operator -(const MWVector<TypeName> &v) const {
    MWVector<TypeName> ret(v.size());
    if (this->size() != v.size()) {
        LOGERROR("[this->size() = " << this->size() << 
                 "] != [v.size() = " << v.size() << 
                 "], can not do operator -");
        return ret;
    }

    for (size_t i = 0; i < this->size(); ++ i) {
        ret[i] = (*this)[i] - v[i];
    }

    return ret;
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::operator -() const {
    MWVector<TypeName> ret(this->size());
    for (size_t i = 0; i < this->size(); ++ i) {
        ret[i] = - (*this)[i];
    }

    return ret;
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::operator -=(const MWVector<TypeName> &v) {
    if (this->size() != v.size()) {
        LOGDEBUG("[this->size() = " << this->size() << 
                 "] != [v.size() = " << v.size() << 
                 "], can not do operator -=");
        return *this;
    }

    for (size_t i = 0; i < this->size(); ++ i) {
        (*this)[i] -= v[i];
    }

    return *this;
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::operator *(const MWVector<TypeName> &v) const {
    MWVector<TypeName> ret(v.size());
    if (this->size() != v.size()) {
        LOGERROR("[this->size() = " << this->size() << 
                 "] != [v.size() = " << v.size() << 
                 "], can not do operator *");
        return ret;
    }

    for (size_t i = 0; i < this->size(); ++ i) {
        ret[i] = (*this)[i] * v[i];
    }

    return ret;
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::operator *(const TypeName &scale) const {
    MWVector<TypeName> ret(this->size());
    for (size_t i = 0; i < this->size(); ++ i) {
        ret[i] = (*this)[i] * scale;
    }

    return ret;
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::operator /(const TypeName &scale) const {
    MWVector<TypeName> ret(this->size());
    for (size_t i = 0; i < this->size(); ++ i) {
        ret[i] = (*this)[i] / scale;
    }

    return ret;
}

template <typename TypeName>
const MWVector<TypeName> MWVector<TypeName>::T() const {
    MWVector<TypeName> ret(this->size());
    for (size_t i = 0; i < this->size(); ++ i) {
        ret[i] = ((*this)[i]).T();
    }

    return ret;
}

template <typename TypeName>
const MWVector<TypeName> &MWVector<TypeName>::Revert() {
    if (this->size() > 1) {
        TypeName item;
        for (size_t i = 0; i < this->size() - i - 1; ++ i) {
            item = (*this)[i];
            (*this)[i] = (*this)[this->size() - i - 1];
            (*this)[this->size() - i - 1] = item;
        }
    }

    return *this;
}

template <typename TypeName>
void MWVector<TypeName>::AddSequence() {
    _len_for_serializing = this->size();
    AddSequenceData(&_len_for_serializing);
    if (this->empty()) {
        return;
    }

    for (size_t i = 0; i < _len_for_serializing; ++ i) {
        AddSequenceData(&((*this)[i]));
    }
}

template <typename TypeName>
void MWVector<TypeName>::AddSequenceForDeserializing() {
    AddSequenceData(&_len_for_serializing);
    TypeName t;
    AddSequenceData(&t);
}

template <typename TypeName>
size_t MWVector<TypeName>::Deserialize(const std::vector<char> &char_vector,
                                     size_t off) {
    SetSequenceForDeserializing();

    size_t len;
    const size_t original_off = off;
    off += (this->*(_deserialize_function_vector[0]))(&len, char_vector, off);

    (*this) = MWVector<TypeName>(len);
    for (size_t i = 0; i < len; ++ i) {
        off += (this->*(_deserialize_function_vector[1]))(&(*this)[i],
                                                               char_vector, off);
    }

    return off - original_off;
}

template <typename TypeName>
const MWVector<TypeName> &MWVector<TypeName>::Concat(const MWVector<TypeName> &v) {
    for (size_t i = 0; i < v.size(); ++ i) {
        this->push_back(v[i]);
    }

    return *this;
}

template <typename TypeName>
const TypeName *MWVector<TypeName>::ToArray(TypeName *array) const {
    for (size_t i = 0; i < this->size(); ++ i) {
        array[i] = (*this)[i];
    }

    return array;
}

template <typename TypeName>
const MWVector<TypeName> &MWVector<TypeName>::Qsort() {
    if (this->empty()) {
        return *this;
    }

    TypeName base[this->size()];
    this->ToArray(base);
    LOGDEBUG("before qsort, *this = " << (*this));

    ::qsort(base, this->size(), sizeof(T), &compare_t<TypeName>);
    *this = MWVector<TypeName>(this->size(), base);
    LOGDEBUG("after qsort, *this = " << (*this));
    return *this;
}

#endif
