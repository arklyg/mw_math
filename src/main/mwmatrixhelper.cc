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


#include "mwmatrixhelper.h"

MWVector<MWVector<MWMatrix<MWData> > > &AssignTimesTransformed(
    const MWVector<MWVector<MWMatrix<MWData> > > &v_m1,
    const MWVector<MWVector<MWMatrix<MWData> > > &v_m2,
    MWVector<MWVector<MWMatrix<MWData> > > &ret) {
    if (v_m1.size() != v_m2.size()) {
        LOGERROR("(v_m1.size() = " << v_m1.size() << 
                 ") != (v_m2.size() = " << v_m2.size() << 
                 "), can not do, return");
        return ret;
    }

    for (size_t i = 0; i < v_m1.size(); ++ i) {
        AssignTimesTransformed(v_m1[i], v_m2[i], ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignPlus(const MWVector<MWMatrix<MWData> > &v1,
                                        const MWVector<MWMatrix<MWData> > &v2, 
                                        MWVector<MWMatrix<MWData> > &ret,
                                        size_t off, 
                                        size_t len) {
    if (v1.size() != v2.size() || v1.size() != ret.size()) {
        LOGERROR("(v1.size() = " << v1.size() << 
                 ") != (v2.size() = " << v2.size() << 
                 ") || (v1.size() = " << v1.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i) {
        AssignPlus(v1[i], v2[i], ret[i]);
    }

    return ret;
}

// len = 0 表示计算到结尾
MWVector<MWMatrix<MWData> > &AssignMinus(const MWVector<MWMatrix<MWData> > &v1,
                                         const MWVector<MWMatrix<MWData> > &v2, 
                                         MWVector<MWMatrix<MWData> > &ret,
                                         size_t off, 
                                         size_t len) {
    if (v1.size() != v2.size() || v1.size() != ret.size()) {
        LOGERROR("(v1.size() = " << v1.size() << 
                 ") != (v2.size() = " << v2.size() << 
                 ") || (v1.size() = " << v1.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i) {
        AssignMinus(v1[i], v2[i], ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignTimes(const MWVector<MWMatrix<MWData> > &v1,
                                         const MWVector<MWMatrix<MWData> > &v2, 
                                         MWVector<MWMatrix<MWData> > &ret,
                                         size_t off, 
                                         size_t len) {
    if (v1.size() != v2.size() || v1.size() != ret.size()) {
        LOGERROR("(v1.size() = " << v1.size() << 
                 ") != (v2.size() = " << v2.size() << 
                 ") || (v1.size() = " << v1.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i) {
        AssignTimes(v1[i], v2[i], ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignTimesTransformed(const MWVector<MWMatrix<MWData> > &v1, 
                                                    const MWVector<MWMatrix<MWData> > &v2,
                                                    MWVector<MWMatrix<MWData> > &ret, 
                                                    size_t off, 
                                                    size_t len) {
    if (v1.size() != v2.size() || v1.size() != ret.size()) {
        LOGERROR("(v1.size() = " << v1.size() << 
                 ") != (v2.size() = " << v2.size() << 
                 ") || (v1.size() = " << v1.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i) {
        AssignTimesTransformed(v1[i], v2[i], ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignDiagonaledTimesTransformed(const MWVector<MWMatrix<MWData> > &v1, 
                                                              const MWVector<MWMatrix<MWData> > &v2,
                                                              MWVector<MWMatrix<MWData> > &ret, 
                                                              size_t off, 
                                                              size_t len) {
    if (v1.size() != v2.size() || v1.size() != ret.size()) {
        LOGERROR("(v1.size() = " << v1.size() << 
                 ") != (v2.size() = " << v2.size() << 
                 ") || (v1.size() = " << v1.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i) {
        AssignDiagonaledTimesTransformed(v1[i], v2[i], ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignDiagonaledTimes(const MWVector<MWMatrix<MWData> > &v1, 
                                                   const MWVector<MWMatrix<MWData> > &v2,
                                                   MWVector<MWMatrix<MWData> > &ret, 
                                                   size_t off, 
                                                   size_t len) {
    if (v1.size() != v2.size() || v1.size() != ret.size()) {
        LOGERROR("(v1.size() = " << v1.size() << 
                 ") != (v2.size() = " << v2.size() << 
                 ") || (v1.size() = " << v1.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i) {
        AssignDiagonaledTimes(v1[i], v2[i], ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignPlus(const MWVector<MWMatrix<MWData> > &v,
                                        const MWMatrix<MWData> &m, 
                                        MWVector<MWMatrix<MWData> > &ret, 
                                        size_t off,
                                        size_t len) {
    if (v.size() != ret.size()) {
        LOGERROR("(v.size() = " << v.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i) {
        AssignPlus(v[i], m, ret[i]);
    }

    return ret;
}


MWVector<MWMatrix<MWData> > &AssignTimes(const MWVector<MWMatrix<MWData> > &v,
                                         const MWMatrix<MWData> &m, 
                                         MWVector<MWMatrix<MWData> > &ret, 
                                         size_t off,
                                         size_t len) {
    if (v.size() != ret.size()) {
        LOGERROR("(v.size() = " << v.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i) {
        AssignTimes(v[i], m, ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignDiagonaledTimesTransformed(const MWVector<MWMatrix<MWData> > &v, 
                                                              const MWMatrix<MWData> &m,
                                                              MWVector<MWMatrix<MWData> > &ret, 
                                                              size_t off, 
                                                              size_t len) {
    if (v.size() != ret.size()) {
        LOGERROR("(v.size() = " << v.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i) {
        AssignDiagonaledTimesTransformed(v[i], m, ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignTimes(const MWVector<MWMatrix<MWData> > &v,
                                         const MWData &scale, 
                                         MWVector<MWMatrix<MWData> > &ret, 
                                         size_t off, 
                                         size_t len) {
    if (v.size() != ret.size()) {
        LOGERROR("(v.size() = " << v.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i) {
        AssignTimes(v[i], scale, ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignTimes(const MWMatrix<MWData> &m,
                                         const MWVector<MWMatrix<MWData> > &v, 
                                         MWVector<MWMatrix<MWData> > &ret,
                                         size_t off, 
                                         size_t len) {
    if (v.size() != ret.size()) {
        LOGERROR("(v.size() = " << v.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i) {
        AssignTimes(m, v[i], ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &AssignSquare(const MWVector<MWMatrix<MWData> > &v,
                                          MWVector<MWMatrix<MWData> > &ret, 
                                          size_t off, 
                                          size_t len) {
    if (v.size() != ret.size()) {
        LOGERROR("(v.size() = " << v.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i) {
        v[i].AssignSquare(ret[i]);
    }

    return ret;
}

MWVector<MWMatrix<MWData> > &Assign(const MWVector<MWMatrix<MWData> > &v,
                                    MWVector<MWMatrix<MWData> > &ret, 
                                    size_t off, 
                                    size_t len) {
    if (v.size() != ret.size()) {
        LOGERROR("(v.size() = " << v.size() << 
                 ") != (ret.size() = " << ret.size() << 
                 "), return.");
        return ret;
    }

    for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i) {
        v[i].Assign(ret[i]);
    }

    return ret;
}

MWMatrix<MWData> &AssignSum(const MWVector<MWMatrix<MWData> > &v,
                            MWMatrix<MWData> &ret, 
                            size_t off, 
                            size_t len) {
    ret = 0;
    for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i) {
        AssignPlus(ret, v[i], ret);
    }

    return ret;
}

MWMatrix<MWData> &AssignPlus(const MWMatrix<MWData> &m1,
                             const MWMatrix<MWData> &m2, 
                             MWMatrix<MWData> &ret) {
    if (m1.GetMatrixInfo() != m2.GetMatrixInfo()) {
        LOGERROR("(m1._info = " << m1.GetMatrixInfo() << 
                 ") != (m2._info = " << m2.GetMatrixInfo() << 
                 ", can not do, return");
        return ret;
    }

    for (size_t i = 0, j; i < m1.GetRowNum(); ++ i) {
        for(j = 0; j < m1.GetColumnNum(); ++ j) {
            ret._data[i][j] = m1._data[i][j] + m2._data[i][j];
        }
    }

    return ret;
}

MWMatrix<MWData> &AssignMinus(const MWMatrix<MWData> &m1,
                              const MWMatrix<MWData> &m2, 
                              MWMatrix<MWData> &ret) {
    if (m1.GetMatrixInfo() != m2.GetMatrixInfo()) {
        LOGERROR("(m1._info = " << m1.GetMatrixInfo() << 
                 ") != (m2._info = " << m2.GetMatrixInfo() << 
                 ", can not do, return");
        return ret;
    }

    for (size_t i = 0, j; i < m1.GetRowNum(); ++ i) {
        for(j = 0; j < m1.GetColumnNum(); ++ j) {
            ret._data[i][j] = m1._data[i][j] - m2._data[i][j];
        }
    }

    return ret;
}

MWMatrix<MWData> &AssignTimes(const MWMatrix<MWData> &m1,
                              const MWMatrix<MWData> &m2, 
                              MWMatrix<MWData> &ret) {
    if (m1.GetColumnNum() != m2.GetRowNum()) {
        LOGERROR("m1._matrix_info = " << m1.GetMatrixInfo() <<
                 ", m2._matrix_info = " << m2.GetMatrixInfo() << 
                 ", can not do operator *");
        return ret;
    }

    for (size_t i_row = 0, i_column, i; i_row < m1.GetRowNum(); ++ i_row) {
        for (i_column = 0; i_column < m2.GetColumnNum(); ++ i_column) {
            for (i = 0; i < m1.GetColumnNum(); ++ i) {
                ret._data[i_row][i_column] = (i == 0 ? 0 : ret._data[i_row][i_column]) +
                                             m1._data[i_row][i] * m2._data[i][i_column];
            }
        }
    }

    return ret;
}

MWMatrix<MWData> &AssignTimesTransformed(const MWMatrix<MWData> &m1,
                                         const MWMatrix<MWData> &m2, 
                                         MWMatrix<MWData> &ret) {
    if (m1.GetColumnNum() != m2.GetColumnNum()) {
        LOGERROR("m1._matrix_info = " << m1.GetMatrixInfo() <<
                 ", m2._matrix_info = " << m2.GetMatrixInfo() << 
                 ", can not do operator *");
        return ret;
    }

    for (size_t i_row = 0, i_column, i; i_row < m1.GetRowNum(); ++ i_row) {
        for (i_column = 0; i_column < m2.GetRowNum(); ++ i_column) {
            for (i = 0; i < m1.GetColumnNum(); ++ i) {
                ret._data[i_row][i_column] = (i == 0 ? 0 : ret._data[i_row][i_column]) +
                                             m1._data[i_row][i] * m2._data[i_column][i];
            }
        }
    }

    return ret;
}

MWMatrix<MWData> &AssignDiagonaledTimesTransformed(const MWMatrix<MWData> &m1, 
                                                   const MWMatrix<MWData> &m2, 
                                                   MWMatrix<MWData> &ret) {
    if (m1.GetRowNum() != m2.GetColumnNum()) {
        LOGERROR("(m1.info = " << m1.GetMatrixInfo() << 
                 "), (m2.info = " << m2.GetMatrixInfo() <<
                 "), can not do AssignDiagonaledTimesTransformed, return");
        return ret;
    }

    for (size_t i = 0, j; i < m2.GetColumnNum(); ++ i) {
        for (j = 0; j < m2.GetRowNum(); ++ j) {
            ret._data[i][j] = m1._data[i][0] * m2._data[j][i];
        }
    }

    return ret;
}

MWMatrix<MWData> &AssignDiagonaledTimes(const MWMatrix<MWData> &m1,
                                        const MWMatrix<MWData> &m2, 
                                        MWMatrix<MWData> &ret) {
    if (m1.GetRowNum() != m2.GetRowNum()) {
        LOGERROR("(m1.info = " << m1.GetMatrixInfo() << 
                 "), (m2.info = " << m2.GetMatrixInfo() << 
                 "), can not do AssignDiagonaledTimes, return");
        return ret;
    }

    for (size_t i = 0, j; i < m2.GetRowNum(); ++ i) {
        for (j = 0; j < m2.GetColumnNum(); ++ j) {
            ret._data[i][j] = m1._data[i][0] * m2._data[i][j];
        }
    }

    return ret;
}

MWMatrix<MWData> &AssignTimes(const MWMatrix<MWData> &m, 
                              const MWData &scale,
                              MWMatrix<MWData> &ret) {
    for (size_t i = 0, j; i < m.GetRowNum(); ++ i) {
        for(j = 0; j < m.GetColumnNum(); ++ j) {
            ret._data[i][j] = m._data[i][j] * scale;
        }
    }

    return ret;
}

