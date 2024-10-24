import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.EthernetSwitch;
import inet.node.inet.StandardHost;

simple Server
{
    parameters:
        @display("i=block/routing");
    gates:
        inout gate;
}

simple Client
{
    parameters:
        @display("i=block/routing");
    gates:
        inout gate;
}

network OpcNetwork
{
    @display("bgb=324,268");
    submodules:
        server: Server {
            parameters:
                @display("i=,purple");
        }
        clientA: Client {
            parameters:
                @display("i=,cyan;p=225,141");
        }
        host1: StandardHost {
            @display("p=52,222");
        }
        host2: StandardHost {
            @display("p=271,222");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=271,37");
        }
        ethernetSwitch: EthernetSwitch {
            @display("p=158,221");
        }
    connections:
        clientA.gate <--> {  delay = 100ms; } <--> server.gate;
        host1.ethg++ <--> Eth100M <--> ethernetSwitch.ethg++;
        ethernetSwitch.ethg++ <--> Eth100M <--> host2.ethg++;
}
