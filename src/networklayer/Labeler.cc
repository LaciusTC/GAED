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

#include "Labeler.h"
#include <string.h>

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/networklayer/common/IpProtocolId_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"

Define_Module(Labeler);

void Labeler::initialize(int stage)
{
    if(stage == inet::INITSTAGE_LOCAL){
        this->status = strToStatus(par("status"));
        WATCH(status);
        WATCH(label);
    }
    else if (stage == inet::INITSTAGE_NETWORK_LAYER) {
        registerService(inet::Protocol::label, nullptr, gate("labelerIn"));
        registerProtocol(inet::Protocol::label, gate("labelerOut"), nullptr);
        if (status == Status::INITIATOR) {
            timer = new omnetpp::cMessage("Start Labeling");
            scheduleAt(omnetpp::getSimulation()->getWarmupPeriod(), timer);
        }
    }
}

void Labeler::handleMessage(omnetpp::cMessage *msg)
{
    if (status != Status::DONE){
        if (msg->isSelfMessage()) { //Temporizador finaliza, iniciador.
            label.setPrefix(15, intuniform(1, 253));
            label.setType(inet::Label::Type::UNICAST);
            auto pkt = Labeler::encapsulate(inet::LabelerPacketType::REQ);
            EV_INFO << "Label: " << label << '\n';
            omnetpp::simtime_t delay = uniform(0, 3);
            sendDelayed(pkt, delay, "labelerOut");
            std::cout << label << '\n';
            status = Status::DONE;
        } else if (msg->arrivedOn("labelerIn")) {   //Procesa y responde.
            auto pkt = inet::check_and_cast<inet::Packet *>(msg);
            processPacket(pkt);
            omnetpp::simtime_t delay = uniform(0, 3);
            sendDelayed(pkt, delay, "labelerOut");
            std::cout << label << '\n';
            status = Status::DONE;
        }
    } else {
        EV_INFO << "I'm DONE\n";
        delete msg;
    }
}

void Labeler::processPacket(inet::Packet *pkt)
{
    pkt->trim();    //Ajustar los apuntadores del paquete
    auto newLabelerHeader = pkt->removeAtFront<inet::LabelerPacket>();
    newLabelerHeader->setTtl(newLabelerHeader->getTtl() - 1);
    label.setLabel(newLabelerHeader->getSrc().toLabel());
    label.setPrefix(newLabelerHeader->getTtl()-1,intuniform(1, 253));
    newLabelerHeader->setSrc(inet::L3Address(label));
    pkt->insertAtFront(newLabelerHeader);

    auto addressReq = pkt->addTagIfAbsent<inet::L3AddressReq>();
    addressReq->setSrcAddress(label);
    addressReq->setDestAddress(inet::Label::BROADCAST_ADDRESS);

    pkt->addTagIfAbsent<inet::DispatchProtocolReq>()->setProtocol(&inet::Protocol::flooding);
    pkt->addTagIfAbsent<inet::PacketProtocolTag>()->setProtocol(&inet::Protocol::label);
}

Labeler::Status Labeler::strToStatus(const char* status) {
    Status sts;
    if (!strcmp(status,"INITIATOR"))
        sts = INITIATOR;
    else if (!strcmp(status,"IDLE"))
        sts = IDLE;
    else
        sts = DONE;
    return sts;
}

// Encapsular paquete.
inet::Packet* Labeler::encapsulate(inet::LabelerPacketType type){
    inet::Packet* labelPacket = new inet::Packet(); // Posible error. (label)
    // Apuntador inteligente (se elimina cuando ya no hay referencias a este).
    auto labelInfo = inet::makeShared<inet::LabelerPacket>();
    // Asignar tipo de mensaje.
    labelInfo->setType(type);
    // Asignar direccion fuente
    labelInfo->setSrc(inet::L3Address(label));
    // Asignar direccion destino
    labelInfo->setDest(inet::Label::BROADCAST_ADDRESS);
    // Asignar estatus
    labelInfo->setStatus(inet::NodeStatus::LABELED);
    // Asignar numero de secuencia
    labelInfo->setSeqNumber(++seqNumber);
    // Asignar tiempo de vida del paquete
    labelInfo->setTtl(16);
    // Insertar cabecera.
    labelPacket->insertAtFront(labelInfo);
    labelPacket->setKind(127);


    // swap src and dest
    // TBD check what to do if dest was multicast etc?
    auto addressReq = labelPacket->addTag<inet::L3AddressReq>();
    addressReq->setSrcAddress(inet::L3Address(label));
    addressReq->setDestAddress(inet::L3Address(label.BROADCAST_ADDRESS));

    labelPacket->addTag<inet::DispatchProtocolReq>()->setProtocol(&inet::Protocol::flooding);
    labelPacket->addTag<inet::PacketProtocolTag>()->setProtocol(&inet::Protocol::label);

    return labelPacket;
}