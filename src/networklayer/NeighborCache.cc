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

#include "NeighborCache.h"

Define_Module(NeighborCache);

NeighborCache::NeighborCache(std::list<entry> &neighborcache) {
    // TODO Auto-generated constructor stub
    this->neighborcache = neighborcache;
    neighborsize = neighborcache.size();
}

NeighborCache::NeighborCache() {
    // TODO Auto-generated destructor stub
    neighborsize = 0;
}

NeighborCache::~NeighborCache() {
    // TODO Auto-generated destructor stub
}

void NeighborCache::initialize(int stage) {
    if(stage == inet::INITSTAGE_NETWORK_LAYER)
        WATCH(neighborsize);

}

void NeighborCache::handleMessage(omnetpp::cMessage* msg) {
    throw omnetpp::cRuntimeError(
            "neighborcache: Este modulo no recibe mensajes.\n"
    );
}

void NeighborCache::insert(const NeighborCache::entry &prefix) {
    Enter_Method_Silent();
    auto it = find(prefix);
    if((it == neighborcache.end())){
        it = std::lower_bound(neighborcache.begin(), neighborcache.end(), prefix);
        neighborcache.insert(it, prefix);
    }
}

std::list<NeighborCache::entry>::const_iterator NeighborCache::begin() const{
    auto it = neighborcache.begin();
    return it;
}

std::list<NeighborCache::entry>::const_iterator NeighborCache::end() const{
    auto it = neighborcache.end();
    return it;
}

std::list<NeighborCache::entry>::iterator NeighborCache::find(const entry &prefix) {
    Enter_Method_Silent();
    auto it = std::find(neighborcache.begin(), neighborcache.end(), prefix);
    return it;
}

//Imprimir los vecinos.
void NeighborCache::showNeighbor(){
    for(auto& i: this->neighborcache){
        std::cout << "\tLabel: " << i.first << " / MAC: " << i.second << "\n";
    }
}