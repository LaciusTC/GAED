//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Label.h"
#include <cstdint>

namespace inet {

Label::Label()
    : addr()
    , type(Type::UNDEFINED)
{ }

Label::Label(uint64_t hi, uint64_t lo) {
    addr.numeric[1] = hi;
    addr.numeric[0] = lo;
    // TODO asignar tipo correcto
    if (addr.symbol[15] == 255) type = BROADCAST;
    else if (addr.symbol[15] == 254) type = MULTICAST;
    else if (!addr.symbol[15]) type = UNDEFINED;
    else type = UNICAST;
}

Label::Label(uint8_t value) // Broadcast
    : addr()
{
    addr.symbol[15] = value;
    // TODO asignar tipo correcto
    if (value == 255) type = BROADCAST;
    else if (value == 254) type = MULTICAST;
    else if (!value) type = UNDEFINED;
    else type = UNICAST;
}

Label::~Label() {
}

const Label Label::UNSPECIFIED_ADDRESS;
const Label Label::BROADCAST_ADDRESS(255);
const Label Label::MULTICAST_ADDRESS(254);
//const Label Label::UNICAST_ADDRESS(1..253);

bool Label::operator==(const Label& label) const { 
    return addr.numeric[1] == label.addr.numeric[1] 
    && addr.numeric[0] == label.addr.numeric[0];
}

Label Label::getPrefix(int prefixLength) { 
    Label label;
    if (prefixLength < 8) { 
        label.addr.numeric[1] = this->addr.numeric[1] & (((1 << (8*prefixLength))-1) << (64-8*prefixLength));
        label.addr.numeric[0] = 0;
    } else {
        label.addr.numeric[0] = this->addr.numeric[0] & (((1 << (8*prefixLength))-1) << (64-8*prefixLength));
        label.addr.numeric[1] = this->addr.numeric[1];
    }
    return label;
}

std::string Label::str() {
    std::string cad;
    for (auto& t : addr.symbol) {
        cad.push_back(t);
    }
    return cad;
}

} // namespace inet