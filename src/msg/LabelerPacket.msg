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

import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;
import inet.networklayer.common.L3Address;
namespace inet;

enum LabelerPacketType {
    REQ   = 10;
    OTHER = 11;
}

enum NodeStatus {
    UNKNOWN   = 0;
    LABELED   = 1;
    UNLABELED = 2;
}
//
// TODO generated message class
//
class LabelerPacket extends FieldsChunk {
    L3Address src;
    L3Address dest;
    LabelerPacketType type;
    NodeStatus status;
    long seqNumber;
    long ttl;
    double x;
    double y;
    chunkLength = B(72); //Longitud en bytes del mensaje.
}