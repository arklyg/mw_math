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


#include "ordervaluefunction.h"

#include <set>

void OrderValueFunction::Initialize(const MWVector<MWVector<MWMatrix<MWData> > >
                                    &data_vector_vector, 
                                    MWData min_value, 
                                    MWData max_value) {
    _min_value = min_value;
    _max_value = max_value;

    if (data_vector_vector.empty()) {
        return;
    }

    size_t _count_eq = 0, 
           _count_gt = 0, 
           _count_ls = 0;

    // 去重
    std::map<MWData, size_t> data_map;
    std::map<MWData, size_t>::iterator finder;
    for (size_t i = 0, j; i < data_vector_vector.size(); ++ i) {
        for (j = 0; j < data_vector_vector[i].size(); ++ j) {
            finder = data_map.find(data_vector_vector[i][j][0][0]);
            if (finder == data_map.end()) {
                data_map.insert(std::pair<MWData, size_t>(data_vector_vector[i][j][0][0], 1));
            } else {
                ++ (finder->second);
            }

            if (data_vector_vector[i][j][0][0] > 0) {
                ++ _count_gt;
            } else if (data_vector_vector[i][j][0][0] < 0) {
                ++ _count_ls;
            } else {
                ++ _count_eq;
            }
        }
    }

    if (data_map.empty()) {
        return;
    }

    MWData unit_value_ls(_min_value / ((MWData) (_count_ls + _count_eq))),
           unit_value_gt(_max_value / ((MWData) (_count_gt + _count_eq)));

    size_t count(0);
    for (finder = data_map.begin(); finder != data_map.end()
            && finder->first < 0; ++ finder) {
        _value_map.insert(
            std::pair<MWData, MWData>(finder->first,
                                 _min_value - unit_value_ls * (((double) count) + ((double) finder->second) / 2)));
        count += finder->second;
    }

    if (finder == data_map.end()) {
        return;
    }

    count = 0;
    if (finder->first == 0) {
        _value_map.insert(std::pair<MWData, MWData>(0, 0));
        count += finder->second;
    }

    for (++ finder; finder != data_map.end(); ++ finder) {
        _value_map.insert(std::pair<MWData, MWData>(finder->first,
                                               unit_value_gt * (((double) count) + ((double) finder->second) / 2)));
        count += finder->second;
    }
}

MWVector<MWData> OrderValueFunction::GetValueStructure(const MWVector<MWData> &input) const {
    return input;
}

MWVector<MWData> &OrderValueFunction::AssignValue(const MWVector<MWData> &input, 
                                                  MWVector<MWData> &ret) const {
    std::map<MWData, MWData>::const_iterator finder;
    for (size_t i = 0; i < input.size(); ++ i) {
        finder = _value_map.find(input[i]);
        ret[i] = finder == _value_map.end() ? 0 : finder->second;
        if (finder == _value_map.end()) {
            LOGWARN("assign_value(" << input[i] <<
                    "), no such key, wrong call. but 0 returned");
        }
        LOGTRACE("before = " << input[i] << 
                 ", after = " << ret[i]);
    }

    return ret;
}
