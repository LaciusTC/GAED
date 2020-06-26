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

package simplenetwork.node;

import inet.linklayer.contract.IWirelessInterface;
import inet.common.MessageDispatcher;
import simplenetwork.applications.Application;
import simplenetwork.networklayer.ExtendedSimpleNetworkLayer;
import inet.networklayer.common.InterfaceTable;
import inet.mobility.contract.IMobility;
//
// TODO auto-generated type
//
module TreeMote
{
    parameters:
        @display("i=misc/sensor2;bgb=522,615");
        @labels(node,ad-hoc-node); // Etiqueta.
        @networkNode;   // Indicar al motor de simulacion que el modulo es un nodo de red.
        int numWlanInterfaces = default(1); // Numero de interfaz inalambrica.
        mobility.subjectModule = default("^"); // Usar propio modelo de mobilidad.
        wlan[*].mgmt.typename = default("Ieee80211MgmtAdhoc");
        wlan[*].agent.typename = default("");
        wlan[*].radio.antenna.mobilityModule = default("^.^.^.mobility");
        wlan[*].radio.antenna.mobility.typename = "";
        //string wRadioType = default("Ieee802154NarrowbandInterface");
        *.interfaceTableModule = default(absPath(".interfaceTable"));
    gates:
        input radioIn[numWlanInterfaces] @directIn;
    submodules:
        wlan[numWlanInterfaces]: <> like IWirelessInterface {
            parameters:
                @display("p=170,547,row,150;q=queue");
        }
        nl: MessageDispatcher {
            parameters:
                @display("p=170,458;b=324,10");
        }
        enl: ExtendedSimpleNetworkLayer {
            @display("p=170,365");
        }
        al: MessageDispatcher {
            parameters:
                @display("p=170,266;b=324,10");
        }
        // application: Application {
        //     @display("p=170,147");
        // }
        interfaceTable: InterfaceTable {
            @display("p=468,420");
        }
        mobility: <default("StationaryMobility")> like IMobility { // Cordenda geografica.
            @display("p=468,320");
        }
    connections:
        radioIn[0] --> { @display("m=s"); } --> wlan[0].radioIn;
        wlan[0].upperLayerOut --> nl.in++;
        nl.out++ --> wlan[0].upperLayerIn;
        enl.ifIn <-- nl.out++;
        enl.ifOut --> nl.in++;
        al.out++ --> enl.transportIn;
        al.in++ <-- enl.transportOut;
        //application.Out --> al.in++;
        //al.out++ --> application.In;
}


