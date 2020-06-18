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

#ifndef BASE_NEIGHBORDISCOVERYPROTOCOLBASE_H_
#define BASE_NEIGHBORDISCOVERYPROTOCOLBASE_H_

#include "../contract/INeighborDiscoveryProtocol.h"
#include "../networklayer/NeighborCache.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
//#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/common/ProtocolTag_m.h"
#include "../msg/Hello_m.h"

class NeighborDiscoveryProtocolBase: public INeighborDiscoveryProtocol {
protected:
    omnetpp::cMessage* broadcastTimer;
    NeighborCache* cache;
    inet::MacAddress mac;
    inet::IInterfaceTable* interfaceTable;
    int interfaceId;
    int hostIndex;
protected:
    virtual void sendPacket(inet::Packet*) = 0;
    virtual void recvPacket(inet::Packet*) = 0;
public:
    NeighborDiscoveryProtocolBase();
    virtual ~NeighborDiscoveryProtocolBase();
    virtual int numInitStages() const override{
        return inet::NUM_INIT_STAGES;
    }
    virtual void initialize(int) override;
};

#endif /* BASE_NEIGHBORDISCOVERYPROTOCOLBASE_H_ */
