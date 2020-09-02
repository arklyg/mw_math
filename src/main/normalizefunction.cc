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


#include "normalizefunction.h"

MWVector<MWData> NormalizeFunction::GetValueStructure(
    const MWVector<MWData> &input) const {
    return MWVector<MWData>(1);
}

MWVector<MWData> &NormalizeFunction::AssignValue(const MWVector<MWData> &input,
                                                 MWVector<MWData> &ret) const {
    // MWData input = input[0], input_min = input[1], input_max = input[2], 
    // output_min = input[3], output_max = input[4];
    ret[0] = (input[0] - input[1]) / (input[2] - input[1]) *
             (input[4] - input[3]) + input[3];
    return ret;
}
