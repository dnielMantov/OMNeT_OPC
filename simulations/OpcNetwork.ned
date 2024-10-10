simple Server
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

simple Client
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
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
        clientA.out --> {  delay = 100ms; } --> server.in;
        clientA.in <-- {  delay = 100ms; } <-- server.out;
}