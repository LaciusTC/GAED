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

#ifndef NETWORKLAYER_EXTENDEDFLOODING_H_
#define NETWORKLAYER_EXTENDEDFLOODING_H_

#include "inet/networklayer/flooding/Flooding.h"

class ExtendedFlooding : public inet::Flooding {
protected:
    /** @brief Handle messages from upper layer */
    virtual void handleUpperPacket(inet::Packet *packet) override;

    /** @brief Handle messages from lower layer */
    virtual void handleLowerPacket(inet::Packet *packet) override;
public:
    ExtendedFlooding();
    virtual ~ExtendedFlooding();
};

#endif /* NETWORKLAYER_EXTENDEDFLOODING_H_ */
