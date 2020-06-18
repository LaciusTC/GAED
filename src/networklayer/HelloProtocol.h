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

#ifndef NETWORKLAYER_HELLOPROTOCOL_H_
#define NETWORKLAYER_HELLOPROTOCOL_H_

#include "../base/NeighborDiscoveryProtocolBase.h"

class HelloProtocol: public NeighborDiscoveryProtocolBase {
protected:
    /** @brief Statistic: number of sent hello msg */
    int msg_counter;
    /** @brief a signal to carry statistics */
    static omnetpp::simsignal_t msgCounterSignal;
    omnetpp::simtime_t bcastDelay;
    int maxAttemps;
protected:
    virtual inet::Packet* encapsulate(inet::HelloMessageType type = inet::HelloMessageType::REQ);
    virtual void sendPacket(inet::Packet*);
    virtual void recvPacket(inet::Packet*);
    virtual omnetpp::simtime_t backoff();
public:
    HelloProtocol();
    virtual ~HelloProtocol();
    /** @brief Initialization of omnetpp.ini parameters*/
    virtual int numInitStages() const override {
      return inet::NUM_INIT_STAGES;
    }
    virtual void initialize(int) override;
    virtual void handleMessage(omnetpp::cMessage*) override;
};

#endif /* NETWORKLAYER_HELLOPROTOCOL_H_ */
