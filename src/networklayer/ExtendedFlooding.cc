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

#include "ExtendedFlooding.h"

ExtendedFlooding::ExtendedFlooding() {
    // TODO Auto-generated constructor stub
}

ExtendedFlooding::~ExtendedFlooding() {
    // TODO Auto-generated destructor stub
}

void ExtendedFlooding::handleUpperPacket(inet::Packet *packet){
    if(packet->getId() == labelerPacketId){
        auto labelerHeader = packet->peekAtFront<inet::LabelerPacket>();
        if(labelerHeader->getSeqNumber() > seqNumber){
            inet::Flooding::encapsulate(packet);
            seqNumber = labelerHeader->getSeqNumber();
        }
    }else inet::Flooding::handleUpperPacket(packet);
    sendDown(packet);
}

void ExtendedFlooding::handleLowerPacket(inet::Packet *packet){}

void ExtendedFlooding::initialize(int stage){
    inet::Flooding::initialize(stage);
    if(stage == inet::INITSTAGE_LOCAL)
        labelerPacketId = par("labelerPacketId");
}

void ExtendedFlooding::encapsulate(inet::Packet *packet){
    inet::L3Address netwAddr;

    EV << "in encaps...\n";

    auto cInfo = packet->removeControlInfo();
    auto pkt = inet::makeShared<inet::LabelerPacket>(); // TODO: packet->getName(), packet->getKind());
    pkt->setChunkLength(inet::b(headerLength));

    auto hopLimitReq = packet->removeTagIfPresent<inet::HopLimitReq>();
    int ttl = (hopLimitReq != nullptr) ? hopLimitReq->getHopLimit() : -1;
    delete hopLimitReq;
    if (ttl == -1)
        ttl = defaultTtl;

    pkt->setSeqNumber(seqNum);
    seqNum++;
    //pkt->setTtl(ttl);

    auto addressReq = packet->findTag<inet::L3AddressReq>();
    if (addressReq == nullptr) {
        EV << "warning: Application layer did not specifiy a destination L3 address\n"
           << "\tusing broadcast address instead\n";
        netwAddr = netwAddr.getAddressType()->getBroadcastAddress();
    }
    else {
        pkt->setProtocol(packet->getTag<inet::PacketProtocolTag>()->getProtocol());
        netwAddr = addressReq->getDestAddress();
        EV << "CInfo removed, netw addr=" << netwAddr << std::endl;
        delete cInfo;
    }

    pkt->setSrcAddr(myNetwAddr);
    pkt->setDestAddr(netwAddr);
    EV << " netw " << myNetwAddr << " sending packet\n";

    EV << "sendDown: nHop=L3BROADCAST -> message has to be broadcasted"
       << " -> set destMac=L2BROADCAST\n";

    pkt->setPayloadLengthField(packet->getDataLength());

    //encapsulate the application packet
    setDownControlInfo(packet, inet::MacAddress::BROADCAST_ADDRESS);

    packet->insertAtFront(pkt);
    EV << " pkt encapsulated\n";
}