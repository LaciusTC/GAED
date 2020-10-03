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
import inet.linklayer.common.MacAddress;
namespace inet;

enum NodeStatus
{
    UNLABELED = 0;
    LABELED = 1;
}

enum HelloMessageType {
    REQ = 10;
    REP = 11;
}
//
// TODO generated message class
//
class Hello extends FieldsChunk {
    string label[20];
    HelloMessageType type;
    NodeStatus status;
    MacAddress srcMacAddress;
    MacAddress destMacAddress;
    double x;    // Position x
    double y;    // Position y
    chunkLength = B(54); //Longitud en bytes del mensaje.
}