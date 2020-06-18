package simplenetwork.base;
import simplenetwork.contract.INeighborDiscoveryProtocol;

simple NeighborDiscoveryProtocolBase like INeighborDiscoveryProtocol {
    parameters:
        @display("i=block/network");
        double broadcastTime @unit(s);
        string interfaceTableModule;
    gates:
        input In @labels(fromNL);
        output Out @labels(toNL);
}