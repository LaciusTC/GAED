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

#include "NeighborDiscoveryProtocolBase.h"

Register_Abstract_Class(NeighborDiscoveryProtocolBase);

NeighborDiscoveryProtocolBase::NeighborDiscoveryProtocolBase()
    : broadcastTimer(nullptr)
    , cache(nullptr)
    , mobil(nullptr)
    , mac()
    , interfaceTable(nullptr)
    , interfaceId(0)
    , hostIndex(0)
    , x(0.0)
    , y(0.0)
{
    // TODO Auto-generated constructor stub
}

NeighborDiscoveryProtocolBase::~NeighborDiscoveryProtocolBase() {
    // TODO Auto-generated destructor stub
    cancelAndDelete(broadcastTimer);
}

void NeighborDiscoveryProtocolBase::initialize(int stage){
    if (stage == inet::INITSTAGE_LOCAL)
    {
        broadcastTime = par("broadcastTime");
        outputGateId = gate("Out")->getId();
        inputGateId = gate("In")->getId();
        broadcastTimer = new omnetpp::cMessage("broadcastTimer");
        hostIndex = inet::getContainingNode(this)->getIndex();
        auto cacheModule = getSimulation()->getSystemModule()->
            getSubmodule("mote", hostIndex)->getSubmodule("enl")->
            getSubmodule("nc");
        cache = static_cast<NeighborCache*>(cacheModule);
        // TODO inicializar apuntador hacia el etiquetador
        interfaceTable = inet::getModuleFromPar<inet::IInterfaceTable>(
            par("interfaceTableModule"), this
        );
        mobil = omnetpp::check_and_cast_nullable<inet::IMobility *>(
            getParentModule()->getParentModule()->getSubmodule("mobility"));
        WATCH(hostIndex);
    }
    else if (stage == inet::INITSTAGE_NETWORK_LAYER)
    {
        interfaceId = interfaceTable->findInterfaceByName("wlan0")->
            getInterfaceId();
        mac = interfaceTable->findInterfaceByName("wlan0")->getMacAddress();
        inet::registerService(
            inet::Protocol::helloProtocol,
            nullptr,
            gate(inputGateId)
        );
        
        inet::registerProtocol(
            inet::Protocol::helloProtocol,
            gate(outputGateId),
            nullptr
        );
    } else if (stage == inet::INITSTAGE_LAST) {
        if (mobil == nullptr) 
            throw omnetpp::cRuntimeError("No mobility module");
        else {
            x = mobil->getCurrentPosition().x;
            y = mobil->getCurrentPosition().y;
            cache->setPosition(x,y);
        }
            
    }
}
