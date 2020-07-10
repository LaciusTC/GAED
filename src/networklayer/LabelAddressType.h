// Copyright (C) 2012 - 2016 Brno University of Technology (http://nes.fit.vutbr.cz/ansa)
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

#ifndef LABEL_ADDRESS_TYPE_H
#define LABEL_ADDRESS_TYPE_H

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/IL3AddressType.h"
#include "inet/networklayer/contract/label/Label.h"

namespace inet {

class INET_API LabelAddressType : public IL3AddressType
{
  public:
    static LabelAddressType INSTANCE;

  public:
    LabelAddressType() {}
    virtual ~LabelAddressType() {}

    virtual int getAddressBitLength() const override { return 128; }
    virtual int getMaxPrefixLength() const override { return 120; }
    virtual L3Address getUnspecifiedAddress() const override { return Label::UNSPECIFIED_ADDRESS; }
    virtual L3Address getBroadcastAddress() const override { return Label::BROADCAST_ADDRESS; }
    virtual L3Address getLinkLocalManetRoutersMulticastAddress() const override { return Label::MULTICAST_ADDRESS; }
    virtual L3Address getLinkLocalRIPRoutersMulticastAddress() const override { return Label::UNSPECIFIED_ADDRESS; }
    virtual const Protocol *getNetworkProtocol() const override { return &Protocol::label; }

    virtual L3Address getLinkLocalAddress(const InterfaceEntry *ie) const override { return Label::UNSPECIFIED_ADDRESS; }
};

} /* namespace inet */

#endif /* ANSA_NETWORKLAYER_CLNS_CLNSADDRESSTYPE_H_ */
