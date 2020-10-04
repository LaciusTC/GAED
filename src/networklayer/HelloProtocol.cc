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

#include "HelloProtocol.h"

Define_Module(HelloProtocol);   //Necesario si se hereda de un modulo simple.

omnetpp::simsignal_t HelloProtocol::msgCounterSignal =
    registerSignal("messageCounter");

HelloProtocol::HelloProtocol()  //Constructor.
    : msg_counter(0)
    , bcastDelay(0.0)
    , maxAttemps(0)
{
    // TODO Auto-generated constructor stub
}

HelloProtocol::~HelloProtocol() {   //Destructor.
}

// Inicializa lo que no es posible inicializar en el constructor.
void HelloProtocol::initialize(int stage) {
    NeighborDiscoveryProtocolBase::initialize(stage);
    if (stage == inet::INITSTAGE_LOCAL) {
        bcastDelay = par("bcastDelay"); //Retraso entre cada msg del broadcast hello.
        maxAttemps = par("maxAttemps").intValue();  //Numero de intentos maximo.
        scheduleAt(omnetpp::simTime() + backoff(), broadcastTimer);
        if (!cache)
            throw omnetpp::cRuntimeError("Hello: module cache not found\n");
    }
}

// Difusion o procesamiento de un mensaje.
void HelloProtocol::handleMessage(omnetpp::cMessage* msg){
    if (msg->isSelfMessage()) { //Temporizador finaliza, broadcast.
        auto pkt = encapsulate();
        sendPacket(pkt);
        // Nuevo tiempo para el siguiente envio.
        scheduleAt(omnetpp::simTime() + backoff(), broadcastTimer);
    } else if (msg->arrivedOn(inputGateId)) {   //Procesa y responde.
        recvPacket(dynamic_cast<inet::Packet*>(msg));
    }
}

// Calculo del retardo.
omnetpp::simtime_t HelloProtocol::backoff(){
    auto delay = bcastDelay < broadcastTime ?
        uniform(0.0, bcastDelay) + broadcastTime :
        broadcastTime;
    return delay;
}

// Encapsular paquete.
inet::Packet* HelloProtocol::encapsulate(inet::HelloMessageType type){
    inet::Packet* helloPacket = new inet::Packet("hello");
    // Apuntador inteligente (se elimina cuando ya no hay referencias a este).
    auto helloInfo = inet::makeShared<inet::Hello>();
    // Asignar tipo de mensaje.
    helloInfo->setType(type);
    // Asignar direccion MAC fuente.
    helloInfo->setSrcMacAddress(mac);
    // Asignar direccion MAC destino.
    helloInfo->setDestMacAddress(inet::MacAddress::BROADCAST_ADDRESS);
    // Asignar coordenadas x, y
    helloInfo->setX(x);
    helloInfo->setY(y);
    // Insertar cabecera.
    helloPacket->insertAtFront(helloInfo);
    return helloPacket;
}

// Send packet.
void HelloProtocol::sendPacket(inet::Packet* pkt){
    // Agregar direccion MAC fuente.
    pkt->addTagIfAbsent<inet::MacAddressReq>()->setSrcAddress(mac);
    // Agregar direccion MAC destino.
    pkt->addTagIfAbsent<inet::MacAddressReq>()->
        setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);
    // Agregar id de la interface.
    pkt->addTagIfAbsent<inet::InterfaceReq>()->setInterfaceId(interfaceId);
    // Agregar Protocolo destino.
    pkt->addTagIfAbsent<inet::PacketProtocolTag>()->
        setProtocol(&inet::Protocol::helloProtocol);
    // Enviar paquete.
    send(pkt, outputGateId);
}

void HelloProtocol::recvPacket(inet::Packet* pkt){
    // Desencapsular paquete.
    auto helloInfo = 
        inet::dynamicPtrCast<inet::Hello>(
        pkt->popAtFront<inet::Hello>()->dupShared()
        );

    // Muestra la fuente del paquete recibido.
    std::cout << "Receive hello packet from " 
    << helloInfo->getSrcMacAddress() << '\n';
    
    // Guardar en la NeighborCache.
    // TODO obtener la etiqueta por apuntador hacia el etiquetador
    cache->insert(NeighborCache::entry("null",helloInfo->getSrcMacAddress(),helloInfo->getX(),helloInfo->getY()));
    
    //std::cout << "Vecindario del nodo " << mac << "\n";
    //cache->showNeighbor();
    
    // Eliminar referencia al paquete.
    delete pkt;
}
