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


#ifndef _MW_MATRIX_H_
#define _MW_MATRIX_H_

#include <mwglobal.h>
#include <mwlogger.h>

#include <mwserializable.h>

#include "mwmathglobal.h"
#include "mwvector.h"
#include "mwmatrixinfo.h"


enum MWVectorAsMatrixType {
    MWVectorAsMatrixTypeRow,
    MWVectorAsMatrixTypeColumn,
    MWVectorAsMatrixTypeDiagonal
};

template <typename TypeName>
class MWMatrix : public MWSerializable {
  public:
    MWVector<MWVector<TypeName> > _data;

  private:
    void init();

  public:
    MWMatrix();
    ~MWMatrix();
    MWMatrix(size_t row_num, size_t column_num, TypeName val = 0);
    MWMatrix(const MWMatrixInfo &info, TypeName val = 0);
    MWMatrix(const MWVector<TypeName> &vector, MWVectorAsMatrixType vector_type);
    MWMatrix(const MWVector<TypeName> &diagonal);
    MWMatrix(const MWVector<MWMatrix<TypeName> > &vector_matrix);

    MWMatrixInfo GetMatrixInfo() const;
    size_t GetRowNum() const;
    size_t GetColumnNum() const;

    MWVector<TypeName> &operator [](size_t i);
    const MWVector<TypeName> &operator [](size_t i) const;

    const MWMatrix<TypeName> &operator =(const MWMatrix<TypeName> &m);
    const MWMatrix<TypeName> &operator =(const TypeName &element);
    const MWMatrix<TypeName> operator +(const MWMatrix<TypeName> &m) const;
    const MWMatrix<TypeName> operator +(const MWVector<MWMatrix<TypeName> > &v_m) const;
    const MWMatrix<TypeName> operator +=(const MWMatrix<TypeName> &m);
    const MWMatrix<TypeName> operator -(const MWMatrix<TypeName> &m) const;
    const MWMatrix<TypeName> operator -=(const MWMatrix<TypeName> &m);
    const MWMatrix<TypeName> operator -() const;
    const MWMatrix<TypeName> operator *(const MWMatrix<TypeName> &m) const;
    const MWMatrix<TypeName> operator *(const TypeName &scale) const;
    const MWVector<MWMatrix<TypeName> > operator *(const MWVector<MWMatrix<TypeName> > &v_m)
    const;
    const MWMatrix<TypeName> operator /(const TypeName &scale) const;
    const MWMatrix<TypeName> T() const;
    const MWMatrix<TypeName> Square() const;
    const MWMatrix<TypeName> AssignSquare(MWMatrix<TypeName> &ret) const;
    const MWMatrix<TypeName> Assign(MWMatrix<TypeName> &ret) const;

    void AddRow(const MWVector<TypeName> &row);
    void AddColumn(const MWVector<TypeName> &column);
    MWMatrix<TypeName> GetRowAsMatrix(size_t row_index,
                               MWVectorAsMatrixType type) const;
    MWMatrix<TypeName> GetColumnAsMatrix(size_t column_index,
                                  MWVectorAsMatrixType type) const;
    MWVector<TypeName> GetRowAsVector(size_t row_index) const;
    MWVector<TypeName> GetColumnAsVector(size_t column_index) const;
    MWMatrix<TypeName> GetRowAverage() const;
    MWMatrix<TypeName> GetColumnAverage() const;

    bool IsEmpty();

    virtual void AddSequence();
};

template <typename TypeName>
std::ostream &operator <<(std::ostream &os, const MWMatrix<TypeName> &m) {
    os << "[";
    for (size_t i = 0, j; i < m.GetRowNum(); ++ i) {
        os << "(";
        for (j = 0; j < m.GetColumnNum(); ++ j) {
            os << m._data[i][j];
            if (j + 1 < m.GetColumnNum()) {
                os << ", ";
            }
        }
        os << ")";
        if (i + 1 < m.GetRowNum()) {
            os << ", ";
        }
    }
    os << "]";

    return os;
}

template <typename TypeName>
const MWVector<MWMatrix<TypeName> > operator *(const MWVector<MWMatrix<TypeName> > &v_m,
                                        const TypeName &scale) {
    MWVector<MWMatrix<TypeName> > ret(v_m.size());
    for (size_t i = 0; i < v_m.size(); ++ i) {
        ret[i] = v_m[i] * scale;
    }

    return ret;
}

template <typename TypeName>
bool operator <(const MWMatrix<TypeName> &m1, const MWMatrix<TypeName> &m2) {
    return m1._data < m2._data;
}

template <typename TypeName>
bool operator >(const MWMatrix<TypeName> &m1, const MWMatrix<TypeName> &m2) {
    return m1._data > m2._data;
}

template <typename TypeName>
bool operator ==(const MWMatrix<TypeName> &m1, const MWMatrix<TypeName> &m2) {
    return m1._data == m2._data;
}

template <typename TypeName>
bool operator !=(const MWMatrix<TypeName> &m1, const MWMatrix<TypeName> &m2) {
    return m1._data != m2._data;
}

template <typename TypeName>
bool operator <=(const MWMatrix<TypeName> &m1, const MWMatrix<TypeName> &m2) {
    return m1._data <= m2._data;
}

template <typename TypeName>
bool operator >=(const MWMatrix<TypeName> &m1, const MWMatrix<TypeName> &m2) {
    return m1._data >= m2._data;
}

template <typename TypeName>
MWMatrix<TypeName>::MWMatrix() {
}

template <typename TypeName>
MWMatrix<TypeName>::~MWMatrix() {
}

template <typename TypeName>
MWMatrix<TypeName>::MWMatrix(size_t row_num, size_t column_num, TypeName val)
    : _data(row_num, MWVector<TypeName>(column_num, val)) {
}

template <typename TypeName>
MWMatrix<TypeName>::MWMatrix(const MWMatrixInfo &info, TypeName val)
    : _data(info._row_num, MWVector<TypeName>(info._column_num, val)) {
}

template <typename TypeName>
MWMatrix<TypeName>::MWMatrix(const MWVector<TypeName> &v, MWVectorAsMatrixType v_type) {
    if (v_type == MWVectorAsMatrixTypeRow) {
        _data.push_back(v);
    } else if (v_type == MWVectorAsMatrixTypeColumn) {
        for (size_t i = 0; i < v.size(); ++ i) {
            _data.push_back(MWVector<TypeName>(1, v[i]));
        }
    } else if (v_type == MWVectorAsMatrixTypeDiagonal) {
        _data = MWVector<MWVector<TypeName> >(v.size(), MWVector<TypeName>(v.size(), TypeName(0)));
        for (size_t i = 0; i < v.size(); ++i) {
            _data[i][i] = v[i];
        }
    }
}

template <typename TypeName>
MWMatrix<TypeName>::MWMatrix(const MWVector<TypeName> &diagonal)
    : _data(diagonal.size(), MWVector<TypeName>(diagonal.size(), TypeName(0))) {
    for (size_t i = 0; i < diagonal.size(); ++ i) {
        _data[i][i] = diagonal[i];
    }
}

template <typename TypeName>
MWMatrix<TypeName>::MWMatrix(const MWVector<MWMatrix<TypeName> > &vector_matrix)
    : _data(vector_matrix[0].GetRowNum(),
            MWVector<TypeName>(vector_matrix[0].GetColumnNum() * vector_matrix.size())) {
    size_t matrix_row_num = vector_matrix[0].GetRowNum(),
           matrix_column_num = vector_matrix[0].GetColumnNum();
    for (size_t k = 0, i, j; k < vector_matrix.size(); ++ k) {
        if (matrix_row_num != vector_matrix[k].GetRowNum()
                || matrix_column_num != vector_matrix[k].GetRowNum()) {
            LOGERROR("(vector_matrix[0]._info = " << vector_matrix[0].GetMatrixInfo() << 
                     ") != (vector_matrix[" << k <<
                     "]._info = " << vector_matrix[k].GetMatrixInfo() << 
                     "), return");
            break;
        }

        for (i = 0; i < matrix_row_num; ++ i) {
            for (j = 0; j < matrix_column_num; ++ j) {
                _data[i][k * matrix_column_num + j] = vector_matrix[k]._data[i][j];
            }
        }
    }
}

template <typename TypeName>
MWMatrixInfo MWMatrix<TypeName>::GetMatrixInfo() const {
    return MWMatrixInfo(GetRowNum(), GetColumnNum());
}

template <typename TypeName>
size_t MWMatrix<TypeName>::GetRowNum() const {
    return _data.size();
}

template <typename TypeName>
size_t MWMatrix<TypeName>::GetColumnNum() const {
    return _data.size() == 0 ? 0 : _data[0].size();
}

template <typename TypeName>
MWVector<TypeName> &MWMatrix<TypeName>::operator [](size_t i) {
    return _data[i];
}

template <typename TypeName>
const MWVector<TypeName> &MWMatrix<TypeName>::operator [](size_t i) const {
    return _data[i];
}

template <typename TypeName>
const MWMatrix<TypeName> &MWMatrix<TypeName>::operator =(const MWMatrix<TypeName> &m) {
    _data = m._data;
    return * this;
}

template <typename TypeName>
const MWMatrix<TypeName> &MWMatrix<TypeName>::operator =(const TypeName &element) {
    for (size_t i = 0; i < GetRowNum(); ++ i) {
        for (size_t j = 0; j < GetColumnNum(); ++ j) {
            _data[i][j] = element;
        }
    }

    return * this;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::operator +(const MWMatrix<TypeName> &m) const {
    if (m.GetMatrixInfo() != GetMatrixInfo()) {
        LOGERROR("(this->_matrix_info = " << GetMatrixInfo() <<
                 ") != (m._matrix_info = " << m.GetMatrixInfo() << 
                 "), can not do operator +");
        return MWMatrix<TypeName>();
    }

    MWMatrix<TypeName> ret(GetMatrixInfo());

    for (size_t i = 0; i < GetRowNum(); ++ i) {
        ret._data[i] = _data[i] + m._data[i];
    }

    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::operator +(const MWVector<MWMatrix<TypeName> > &v_m)
const {
    MWVector<MWMatrix<TypeName> > ret(*this);

    for (size_t i = 0; i < v_m.size(); ++ i) {
        ret[i] += v_m[i];
    }

    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::operator +=(const MWMatrix<TypeName> &m) {
    if (m.GetMatrixInfo() != GetMatrixInfo()) {
        LOGERROR("(this->_matrix_info = " << GetMatrixInfo() <<
                 ") != (m._matrix_info = " << m.GetMatrixInfo() <<
                 "), can not do operator +=");
        return *this;
    }

    for (size_t i = 0; i < GetRowNum(); ++ i) {
        _data[i] += m._data[i];
    }

    return *this;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::operator -(const MWMatrix<TypeName> &m) const {
    if (m.GetMatrixInfo() != GetMatrixInfo()) {
        LOGERROR("(this->_matrix_info = " << GetMatrixInfo() <<
                 ") != (m._matrix_info = " << m.GetMatrixInfo() << 
                 "), can not do operator -");
        return MWMatrix<TypeName>();
    }

    MWMatrix<TypeName> ret(GetMatrixInfo());

    for (size_t i = 0; i < GetRowNum(); ++ i) {
        ret._data[i] = _data[i] - m._data[i];
    }

    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::operator -=(const MWMatrix<TypeName> &m) {
    if (m.GetMatrixInfo() != GetMatrixInfo()) {
        LOGERROR("(this->_matrix_info = " << GetMatrixInfo() <<
                 ") != (m._matrix_info = " << m.GetMatrixInfo() <<
                 "), can not do operator -=");
        return *this;
    }

    for (size_t i = 0; i < GetRowNum(); ++ i) {
        _data[i] -= m._data[i];
    }

    return *this;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::operator -() const {
    MWMatrix<TypeName> ret;
    ret._data = - _data;
    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::operator *(const MWMatrix<TypeName> &m) const {
    if (GetColumnNum() != m.GetRowNum()) {
        LOGERROR("this->_matrix_info = " << GetMatrixInfo() <<
                  ", m._matrix_info = " << m.GetMatrixInfo() << ", can not do operator *");
        return MWMatrix<TypeName>();
    }

    MWMatrix<TypeName> ret(GetRowNum(), m.GetColumnNum());

    for (size_t i_row = 0, i_column, i; i_row < GetRowNum(); ++ i_row) {
        for (i_column = 0; i_column < m.GetColumnNum(); ++ i_column) {
            for (i = 0; i < GetColumnNum(); ++ i) {
                ret._data[i_row][i_column] += _data[i_row][i] * m._data[i][i_column];
            }
        }
    }

    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::operator *(const TypeName &scale) const {
    MWMatrix<TypeName> ret(GetMatrixInfo());

    for (size_t i = 0; i < GetRowNum(); ++ i) {
        ret._data[i] = _data[i] * scale;
    }

    return ret;
}

template <typename TypeName>
const MWVector<MWMatrix<TypeName> > MWMatrix<TypeName>::operator *(
    const MWVector<MWMatrix<TypeName> > &v_m) const {
    MWVector<MWMatrix<TypeName> > ret(v_m.size());

    for (size_t i = 0; i < v_m.size(); ++ i) {
        ret[i] = *this * v_m[i];
    }

    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::operator /(const TypeName &scale) const {
    MWMatrix<TypeName> ret(GetMatrixInfo());

    for (size_t i = 0; i < GetRowNum(); ++ i) {
        ret._data[i] = _data[i] / scale;
    }

    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::T() const {
    MWMatrix<TypeName> ret(GetColumnNum(), GetRowNum());

    for (size_t i = 0, j; i < GetRowNum(); ++ i) {
        for (j = 0; j < GetColumnNum(); ++ j) {
            ret._data[j][i] = _data[i][j];
        }
    }

    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::Square() const {
    MWMatrix<TypeName> ret(GetMatrixInfo());
    for (size_t i = 0, j; i < GetRowNum(); ++ i) {
        for (j = 0; j < GetColumnNum(); ++ j) {
            ret._data[i][j] = _data[i][j] * _data[i][j];
        }
    }

    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::AssignSquare(MWMatrix<TypeName> &ret) const {
    for (size_t i = 0, j; i < GetRowNum(); ++ i) {
        for (j = 0; j < GetColumnNum(); ++ j) {
            ret._data[i][j] = _data[i][j] * _data[i][j];
        }
    }

    return ret;
}

template <typename TypeName>
const MWMatrix<TypeName> MWMatrix<TypeName>::Assign(MWMatrix<TypeName> &ret) const {
    for (size_t i = 0, j; i < GetRowNum(); ++ i) {
        for (j = 0; j < GetColumnNum(); ++ j) {
            ret._data[i][j] = _data[i][j];
        }
    }

    return ret;
}

template <typename TypeName>
void MWMatrix<TypeName>::AddRow(const MWVector<TypeName> &row) {
    if (!IsEmpty() && row.size() != GetColumnNum()) {
        LOGERROR("this matrix [size = (" << GetRowNum() << " * " <<
                  GetColumnNum() << " )] can not add this vector [ size = " << row.size() <<
                  " ] as row");
        return;
    }

    _data.push_back(row);
}

template <typename TypeName>
void MWMatrix<TypeName>::AddColumn(const MWVector<TypeName> &column) {
    if (!IsEmpty() && column.size() != GetColumnNum()) {
        LOGERROR("this matrix [size = (" << GetRowNum() << 
                 " * " << GetColumnNum() << 
                 " )] can not add this vector [ size = " << column.size() <<
                 " ] as column");
        return;
    }

    for (size_t i = 0; i < GetColumnNum(); ++ i) {
        _data[i].push_back(column[i]);
    }
}

template <typename TypeName>
MWMatrix<TypeName> MWMatrix<TypeName>::GetRowAsMatrix(size_t row_index,
                                        MWVectorAsMatrixType type) const {
    if (row_index >= GetRowNum()) {
        LOGERROR("( row_index = " << row_index <<
                 " ) >= ( this matrix row num = " << GetRowNum() << 
                 " )");
        return MWMatrix<TypeName>();
    }

    MWMatrix<TypeName> ret(type == MWVectorAsMatrixTypeRow ? 1 : GetColumnNum(),
                    type == MWVectorAsMatrixTypeRow ? GetColumnNum() : 1);
    for (size_t i = 0; i < GetColumnNum(); ++ i) {
        ret._data[type == MWVectorAsMatrixTypeRow ? 0 : i][type == MWVectorAsMatrixTypeRow ? i : 0] = 
            _data[row_index][i];
    }

    return ret;
}

template <typename TypeName>
MWMatrix<TypeName> MWMatrix<TypeName>::GetColumnAsMatrix(size_t column_index,
                                           MWVectorAsMatrixType type) const {
    if (column_index >= GetColumnNum()) {
        LOGERROR("( column_index = " << column_index <<
                 " ) >= ( this matrix column num = " << GetColumnNum() << 
                 " )");
        return MWMatrix<TypeName>();
    }

    MWMatrix<TypeName> ret(type == MWVectorAsMatrixTypeColumn ? GetRowNum() : 1,
                    type == MWVectorAsMatrixTypeColumn ? 1 : GetRowNum());
    for (size_t i = 0; i < GetRowNum(); ++ i) {
        ret._data[type == MWVectorAsMatrixTypeColumn ? i : 0][type == MWVectorAsMatrixTypeColumn ? 0 : i] = 
            _data[i][column_index];
    }

    return ret;
}

template <typename TypeName>
MWVector<TypeName> MWMatrix<TypeName>::GetRowAsVector(size_t row_index) const {
    if (row_index >= GetRowNum()) {
        LOGERROR("row_index > this row num");
        return MWVector<TypeName>();
    }

    return _data[row_index];
}

template <typename TypeName>
MWVector<TypeName> MWMatrix<TypeName>::GetColumnAsVector(size_t column_index) const {
    if (column_index >= GetColumnNum()) {
        LOGERROR("column_index > this column num");
        return MWVector<TypeName>();
    }

    MWVector<TypeName> ret(GetRowNum());
    for (size_t i = 0; i < GetRowNum(); ++ i) {
        ret[i] = _data[i][column_index];
    }

    return ret;
}

template <typename TypeName>
MWMatrix<TypeName> MWMatrix<TypeName>::GetRowAverage() const {
    MWMatrix<TypeName> ret(1, GetColumnNum());

    for (size_t i = 0, j; i < GetRowNum(); ++ i) {
        for (j = 0; j < GetColumnNum(); ++ j) {
            ret._data[0][j] += _data[i][j];
        }
    }

    return ret / GetRowNum();
}

template <typename TypeName>
MWMatrix<TypeName> MWMatrix<TypeName>::GetColumnAverage() const {
    MWMatrix<TypeName> ret(GetRowNum(), 1);

    for (size_t i = 0, j; i < GetRowNum(); ++ i) {
        for (j = 0; j < GetColumnNum(); ++ j) {
            ret._data[i][0] += _data[i][j];
        }
    }

    return ret / GetColumnNum();
}

template <typename TypeName>
bool MWMatrix<TypeName>::IsEmpty() {
    return GetRowNum() == 0 || GetColumnNum() == 0;
}

template <typename TypeName>
void MWMatrix<TypeName>::AddSequence() {
    AddSequenceData(&_data);
}

#endif
