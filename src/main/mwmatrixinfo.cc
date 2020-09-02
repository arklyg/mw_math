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


#include "mwmatrixinfo.h"

MWMatrixInfo::MWMatrixInfo(size_t row_num, size_t column_num)
    : _row_num(row_num)
    , _column_num(column_num) {
}

bool MWMatrixInfo::operator ==(const MWMatrixInfo &info) {
    return _row_num == info._row_num && _column_num == info._column_num;
}

bool MWMatrixInfo::operator !=(const MWMatrixInfo &info) {
    return !(*this == info);
}

void MWMatrixInfo::AddSequence() {
    AddSequenceData(&_row_num);
    AddSequenceData(&_column_num);
}

std::ostream &operator <<(std::ostream &os, const MWMatrixInfo &info) {
    os << "(_row_num = " << info._row_num << ", _column_num = " << info._column_num
       << ")";

    return os;
}
