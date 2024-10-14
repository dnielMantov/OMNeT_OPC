#include <omnetpp.h>
#include "opcserver.h"

using namespace omnetpp;

class Client : public cSimpleModule
{
    private:
        int counter;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Client);

void Client::initialize()
{
    counter = 10;
    WATCH(counter);
    cMessage *msg = new cMessage(std::to_string(counter).c_str());
    send(msg, "gate$o");
}

void Client::handleMessage(cMessage *msg)
{
    EV << msg->getName() << endl;
    msg->setName(std::to_string(--counter).c_str());
    send(msg, "gate$o");
}
