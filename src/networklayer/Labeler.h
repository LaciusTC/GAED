//
// Copyright (C) 2004, 2009 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef LABELER_H
#define LABELER_H

#include "inet/common/INETDefs.h"
#include "inet/common/packet/Packet.h"
#include "../msg/LabelerPacket_m.h"
#include "inet/networklayer/common/L3Address.h"
#include "Label.h"

/**
 * TODO
 */
class Labeler : public omnetpp::cSimpleModule
{
  public:
    enum Status {
      INITIATOR = 1,
      IDLE,
      DONE
    };

  protected:
    Status status;
    inet::Label label;
    omnetpp::cMessage* timer;
    long seqNumber;

  protected:
    virtual void processPacket(inet::Packet*);
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;
    virtual Status strToStatus(const char*);
    virtual inet::Packet* encapsulate(inet::LabelerPacketType type = inet::LabelerPacketType::OTHER);

  public:
    Labeler()
      : status(Status::IDLE)
      , label()
      , timer(nullptr)
      , seqNumber(0)
    {}
    ~Labeler() {
      if (timer)
        cancelAndDelete(timer);
    }
};

#endif // ifndef LABELER_H

