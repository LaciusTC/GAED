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

#ifndef NETWORKLAYER_LABEL_H_
#define NETWORKLAYER_LABEL_H_
#include <cstdint>
#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>

namespace inet {

class Label {
public:
    typedef union address_t {
        uint8_t symbol[16]; // symbol[15] : root
        uint64_t numeric[2]; // 0 : lo, 1 : hi
        address_t() : numeric {0,0} {}
    } Address;
    enum Type {
        UNDEFINED = 0,
        UNICAST = 1,
        MULTICAST = 254,
        BROADCAST = 255
    };
protected:
    Address addr;
    Type type;
public:
    Label(); // Constructor por omision
    Label(uint64_t, uint64_t); // Constructor numerico
    Label(uint8_t); // Constructor por prefijo
    virtual ~Label();
    static const Label UNSPECIFIED_ADDRESS; // Todo cero.
    static const Label UNICAST_ADDRESS; // 
    static const Label BROADCAST_ADDRESS; // Byte mas significativo en 1.
    static const Label MULTICAST_ADDRESS; // Prefijo de direccion multicast.
    
    std::string str();
    Address getLabel() const { return addr; }
    Label getPrefix(int);
    uint8_t getSymbol(size_t i) const { return addr.symbol[i]; }
    void setLabel(const Label& label) {this->addr = label.addr; this->type = label.type;}
    void setLabel(Address addr, Type t) { this->addr = addr; this->type = t;}
    void setPrefix(uint8_t index, uint8_t value) { addr.symbol[index] = value; }
    void setType(Type t) { type = t; }

    bool assertSize(const char* cad) { return sizeof(cad)-1 == 16; }
    bool isUnspecified() { return !addr.numeric[0] && !addr.numeric[1]; }
    bool isUnicast() { return addr.symbol[15] && addr.symbol[15] < 254; }
    bool isMulticast() { return addr.symbol[15] == 254; }
    bool isBroadcast() { return addr.symbol[15] == 255; }

    bool operator<(const Label& label) const { return addr.numeric[1] < label.addr.numeric[1]; }
    bool operator<=(const Label& label) const { return addr.numeric[1] <= label.addr.numeric[1]; }
    bool operator>(const Label& label) const { return addr.numeric[1] > label.addr.numeric[1]; }
    bool operator>=(const Label& label) const { return addr.numeric[1] >= label.addr.numeric[1]; }
    bool operator==(const Label&) const;
    bool operator!=(const Label& label) const { return !(*this == label); }

    bool matches(const Label& label, int prefixLength) { return false; } // TODO implementar para encaminamiento.
};

inline std::ostream& operator<<(std::ostream& os, const Label& address)
{
    for (int i = 15; i >= 0; i--) {
        if (i > 0)
            os << std::setfill('0') << std::setw(2) << std::hex 
               << static_cast<int>(address.getSymbol(i)) << ':';
        else
            os << std::setfill('0') << std::setw(2) << std::hex 
               << static_cast<int>(address.getSymbol(i));
    }
    return os;
}

} // namespace inet

#endif /* NETWORKLAYER_LABEL_H_ */
