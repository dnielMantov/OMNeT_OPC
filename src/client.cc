#include <omnetpp.h>
#include "opcserver.h"
#include "messageUpdate_m.h"

using namespace omnetpp;

class Client : public cSimpleModule
{
    private:
        int messageValue;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Client);

void Client::initialize()
{
    messageValue = 10;
    MessageUpdate *msgUp = new MessageUpdate();
    msgUp->setValue(messageValue);
    WATCH(messageValue);
    send(msgUp, "gate$o");
}

void Client::handleMessage(cMessage *msg)
{
    MessageUpdate *msgUp = check_and_cast<MessageUpdate *>(msg);

    EV << msgUp->getValue() << endl;

    msgUp->setValue(--messageValue);
    
    send(msgUp, "gate$o");
}
