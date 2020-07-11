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

package simplenetwork.networklayer;

import inet.networklayer.common.SimpleNetworkLayer;
import simplenetwork.contract.INeighborDiscoveryProtocol;
import simplenetwork.networklayer.HelloProtocol;
import simplenetwork.networklayer.Labeler;
//
// TODO auto-generated type
//
module ExtendedSimpleNetworkLayer extends SimpleNetworkLayer
{
    parameters:
        @display("i=block/fork");
    submodules:
        // ndp: <default("HelloProtocol")> like INeighborDiscoveryProtocol {
        //     @display("p=461,300");
        // }
        // nc: NeighborCache {
        //     @display("p=520,300");
        // }
        labeler: Labeler{
            @display("p=150,100");
        }
    connections:
        // lp.out++ --> ndp.In;
        // ndp.Out --> lp.in++;
        labeler.labelerIn <-- up.out++;
        labeler.labelerOut --> up.in++;

}
