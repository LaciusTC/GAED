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
        else encapsulate(packet);
    }
    else inet::Flooding::encapsulate(packet);

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

void ExtendedFlooding::handleLowerPacket(inet::Packet *packet)
{
    auto floodHeader = packet->peekAtFront<inet::FloodingHeader>();

    //msg not broadcasted yet
    if (notBroadcasted(floodHeader.get())) {
        if(packet->getId() == labelerPacketId){ // TODO checar que el paquete sea broadcast.
            if(floodHeader->getTtl() >= 1){
                labelerTtl = floodHeader->getTtl() - 1;
                // message has to be forwarded to upper layer
                nbHops = nbHops + (defaultTtl + 1 - floodHeader->getTtl());
                decapsulate(packet);
                sendUp(packet);
                nbDataPacketsReceived++;
            }else{
                EV_INFO << "labelerPacket has reached max number of hops.\n";
                delete packet;
            }
        }
        //msg is for me
        else if (interfaceTable->isLocalAddress(floodHeader->getDestinationAddress())) {
            EV << " data msg for me! send to Upper\n";
            nbHops = nbHops + (defaultTtl + 1 - floodHeader->getTtl());
            decapsulate(packet);
            sendUp(packet);
            nbDataPacketsReceived++;
        }
        //broadcast message
        else if (floodHeader->getDestinationAddress().isBroadcast()) {
            
            //check ttl and rebroadcast
            if (floodHeader->getTtl() > 1) {
                EV << " data msg BROADCAST! ttl = " << floodHeader->getTtl()
                   << " > 1 -> rebroadcast msg & send to upper\n";
                auto dMsg = packet->dup();
                auto newFloodHeader = dMsg->removeAtFront<inet::FloodingHeader>();
                newFloodHeader->setTtl(newFloodHeader->getTtl() - 1);
                dMsg->insertAtFront(newFloodHeader);
                setDownControlInfo(dMsg, inet::MacAddress::BROADCAST_ADDRESS);
                sendDown(dMsg);
                nbDataPacketsForwarded++;
            }
            else
                EV << " max hops reached (ttl = " << floodHeader->getTtl() << ") -> only send to upper\n";

            // message has to be forwarded to upper layer
            nbHops = nbHops + (defaultTtl + 1 - floodHeader->getTtl());
            decapsulate(packet);
            sendUp(packet);
            nbDataPacketsReceived++;
        }
        //not for me -> rebroadcast
        else {
            //check ttl and rebroadcast
            if (floodHeader->getTtl() > 1) {
                EV << " data msg not for me! ttl = " << floodHeader->getTtl()
                   << " > 1 -> forward\n";
                decapsulate(packet);
                auto packetCopy = new inet::Packet();
                packetCopy->insertAtBack(packet->peekDataAt(inet::b(0), packet->getDataLength()));
                auto floodHeaderCopy = inet::staticPtrCast<inet::FloodingHeader>(floodHeader->dupShared());
                floodHeaderCopy->setTtl(floodHeader->getTtl() - 1);
                packetCopy->insertAtFront(floodHeaderCopy);
                // needs to set the next hop address again to broadcast
                cObject *const pCtrlInfo = packetCopy->removeControlInfo();
                if (pCtrlInfo != nullptr)
                    delete pCtrlInfo;
                setDownControlInfo(packetCopy, inet::MacAddress::BROADCAST_ADDRESS);
                sendDown(packetCopy);
                nbDataPacketsForwarded++;
                delete packet;
            }
            else {
                //max hops reached -> delete
                EV << " max hops reached (ttl = " << floodHeader->getTtl() << ") -> delete msg\n";
                delete packet;
            }
        }
    }
    else {
        EV << " data msg already BROADCASTed! delete msg\n";
        delete packet;
    }
}

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