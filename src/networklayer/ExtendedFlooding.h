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

#ifndef NETWORKLAYER_EXTENDEDFLOODING_H_
#define NETWORKLAYER_EXTENDEDFLOODING_H_

#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/flooding/Flooding.h"
#include "../msg/LabelerPacket_m.h"
//#include "inet/networklayer/flooding/FloodingHeader_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"
#include <unordered_map>

class ExtendedFlooding : public inet::Flooding {
protected:
    //std::unordered_map<unsigned, unsigned>labelerPacketTtl;
    unsigned labelerPacketId;
    unsigned seqNumber;
    unsigned ttl;
protected:
    /** @brief Handle messages from upper layer */
    virtual void handleUpperPacket(inet::Packet *packet) override;

    /** @brief Handle messages from lower layer */
    virtual void handleLowerPacket(inet::Packet *packet) override;

    virtual void encapsulate(inet::Packet *packet);
public:
    ExtendedFlooding();
    virtual ~ExtendedFlooding();
    virtual void initialize(int) override;
};

#endif /* NETWORKLAYER_EXTENDEDFLOODING_H_ */
