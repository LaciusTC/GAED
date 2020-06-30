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
        if(labelerHeader->getSeqNumber() > labelerSequenceNumber){
            inet::Flooding::encapsulate(packet);
            labelerSequenceNumber = labelerHeader->getSeqNumber();
        }
        else{
            encapsulate(packet);
        }
    }
    else
    {
        inet::Flooding::encapsulate(packet);
    }
    auto floodHeader = packet->peekAtFront<inet::FloodingHeader>();
    if (plainFlooding) {
        if (bcMsgs.size() >= bcMaxEntries) {
            //search the broadcast list of outdated entries and delete them
            for (auto it = bcMsgs.begin(); it != bcMsgs.end(); ) {
                if (it->delTime < omnetpp::simTime())
                    it = bcMsgs.erase(it);
                else
                    ++it;
            }
            //delete oldest entry if max size is reached
            if (bcMsgs.size() >= bcMaxEntries) {
                EV << "bcMsgs is full, delete oldest entry" << std::endl;
                bcMsgs.pop_front();
            }
        }
        bcMsgs.push_back(Bcast(floodHeader->getSeqNum(), floodHeader->getSourceAddress(), omnetpp::simTime() + bcDelTime));
    }
    //there is no routing so all messages are broadcast for the mac layer
    sendDown(packet);
    nbDataPacketsSent++;
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
    auto pkt = inet::makeShared<inet::FloodingHeader>(); // TODO: packet->getName(), packet->getKind());
    pkt->setChunkLength(inet::b(headerLength));

    auto hopLimitReq = packet->removeTagIfPresent<inet::HopLimitReq>();
    delete hopLimitReq;

    pkt->setSeqNum(seqNum);
    seqNum++;
    pkt->setTtl(labelerTtl);

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