simple Server
{
    parameters:
        @display("i=block/routing");
    gates:
        inout gate[];
}

simple Client
{
    parameters:
        @display("i=block/routing");
    gates:
        inout gate[];
}

network OpcNetwork
{
    @display("bgb=627,432");
    submodules:
        server[1]: Server {
            parameters:
                @display("i=,purple;p=315,225");
        }
        clientA[1]: Client {
            parameters:
                @display("i=,cyan;p=164,335");
        }
        clientB[1]: Client {
            parameters:
                @display("i=,cyan;p=164,132");
        }
        clientC[1]: Client {
            parameters:
                @display("i=,cyan;p=315,60");
        }
        clientD[1]: Client {
            parameters:
                @display("i=,cyan;p=457,142");
        }
        clientE[1]: Client {
            parameters:
                @display("i=,cyan;p=451,335");
        }
    connections:
        clientA[0].gate++ <--> {  delay = 10ms; } <--> server[0].gate++;
        clientB[0].gate++ <--> {  delay = 10ms; } <--> server[0].gate++;
        clientC[0].gate++ <--> {  delay = 10ms; } <--> server[0].gate++;
        clientD[0].gate++ <--> {  delay = 10ms; } <--> server[0].gate++;
        clientE[0].gate++ <--> {  delay = 10ms; } <--> server[0].gate++;
}
