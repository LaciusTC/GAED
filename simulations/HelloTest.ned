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

package simplenetwork.simulations;

import simplenetwork.node.TreeMote;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;

//
// TODO auto-generated type
//
network HelloTest
{
    parameters:
        @display("bgb=160,150;bgg=,,grey10");
        int moteNumber = default(2);
    submodules:
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=150,20;is=s");
        }
        mote[moteNumber]: TreeMote {
            @display("p=100,100");
        }
    connections allowunconnected:
}
