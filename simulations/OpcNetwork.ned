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
    submodules:
        server: Server {
            parameters:
                @display("i=,purple");
        }
        clientA: Client {
            parameters:
                @display("i=,cyan");
        }
    connections:
        clientA.gate <--> {  delay = 100ms; } <--> server.gate;
}