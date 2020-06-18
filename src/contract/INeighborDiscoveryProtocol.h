#ifndef INEIGHBORDISCOVERYPROTOCOL
#define INEIGHBORDISCOVERYPROTOCOL

#include "inet/common/INETDefs.h" //Se agrega si se usa un modulo de inet.
#include "inet/common/packet/Packet.h" //Si se exetiende el framework de inet, se usan paquetes de inet.
#include <omnetpp.h>

class INeighborDiscoveryProtocol : public omnetpp::cSimpleModule{
protected:
    omnetpp::simtime_t broadcastTime;
    int outputGateId;
    int inputGateId;
protected:
    virtual void sendPacket(inet::Packet*) = 0;
    virtual void recvPacket(inet::Packet*) = 0;
public:
    INeighborDiscoveryProtocol()
    : broadcastTime(0.0)
    , outputGateId(0)
    , inputGateId(0)
    {}
    virtual ~INeighborDiscoveryProtocol(){}
};

Register_Abstract_Class(INeighborDiscoveryProtocol);

#endif
