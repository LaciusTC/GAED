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

#ifndef NETWORKLAYER_NEIGHBORCACHE_H_
#define NETWORKLAYER_NEIGHBORCACHE_H_

#include <omnetpp/csimplemodule.h>
#include <string>
#include <list>
#include <algorithm>
#include <tuple>
#include "inet/common/INETDefs.h"
#include "inet/linklayer/common/MacAddressTag_m.h"

class NeighborCache : public omnetpp::cSimpleModule
{
public:
    typedef std::tuple<std::string,inet::MacAddress,double,double> entry;
private:
    std::list<entry> neighborcache; // (Etiqueta, MAC)
    int neighborsize;
    double x, y;
protected:
    virtual int numInitStages() const override {return inet::NUM_INIT_STAGES;}
    virtual void initialize(int stage) override;
    virtual void handleMessage(omnetpp::cMessage*) override;
    virtual void drawArrow(const entry&);
    std::list<entry>::const_iterator begin() const;
    std::list<entry>::const_iterator end() const;
    std::list<entry>::iterator find(const entry&);
public:
    virtual void insert(const entry&);
    virtual void showNeighbor();
    virtual void setPosition(double x,double y) {this->x=x; this->y=y;}
    virtual std::pair<double,double> getNeighborPosition(const std::string&);
    NeighborCache(std::list<entry>&);
    NeighborCache();
    ~NeighborCache();
};

#endif /* NETWORKLAYER_NEIGHBORCACHE_H_ */
