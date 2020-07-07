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
        const char* status = par("status");
        this->status = strToStatus(status);
    }
    else if (stage == inet::INITSTAGE_NETWORK_LAYER) {
        registerService(inet::Protocol::label, nullptr, gate("labelerIn"));
        registerProtocol(inet::Protocol::label, gate("labelerOut"), nullptr);
        if (status == Status::INITIATOR) {
            timer = new omnetpp::cMessage("Start Labelering");
            scheduleAt(omnetpp::getSimulation()->getWarmupPeriod(), timer);
        }
    }
}

void Labeler::handleMessage(omnetpp::cMessage *msg)
{
    if (status != Status::DONE){
        if (msg->isSelfMessage()) { //Temporizador finaliza, iniciador.
            label.setPrefix(0,intuniform(1, 253));
            auto pkt = Labeler::encapsulate(inet::LabelerPacketType::REQ);
            send(pkt, "labelerOut");
            status = Status::DONE;
        } else if (msg->arrivedOn("labelerIn")) {   //Procesa y responde.
            auto pkt = inet::check_and_cast<inet::Packet *>(msg);
            auto labelerHeader = pkt->peekAtFront<inet::LabelerPacket>();
            label.setPrefix(labelerHeader->getTtl()-1,intuniform(1, 253));
            processPacket(pkt);
            send(pkt, "labelerOut");
            status = Status::DONE;
            delete pkt;
        }
    } else {
        EV_INFO << "I'm DONE\n";
        delete msg;
    }
}

void Labeler::processPacket(inet::Packet *pkt)
{
    auto dPkt = pkt->dup();
    auto newLabelerHeader = dPkt->removeAtFront<inet::LabelerPacket>();
    newLabelerHeader->setTtl(newLabelerHeader->getTtl() - 1);
    newLabelerHeader->setSrc(inet::L3Address(label));
    dPkt->insertAtFront(newLabelerHeader);
    pkt = dPkt;
    delete dPkt;
}

Labeler::Status Labeler::strToStatus(const char* status) {
    Status sts;
    if (status == "INITIATOR")
        sts = INITIATOR;
    else if (status == "IDLE")
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
    labelInfo->setSeqNumber(seqNumber++);
    // Asignar tiempo de vida del paquete
    labelInfo->setTtl(16);
    // Insertar cabecera.
    labelPacket->insertAtFront(labelInfo);
    return labelPacket;
}