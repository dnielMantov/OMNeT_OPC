#include <omnetpp.h>
#include "opcserver.h"
#include "messageUpdate_m.h"
#include "random"

using namespace omnetpp;

class Client : public cSimpleModule
{
    private:
        double messageValue;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual double generateValue();
};

Define_Module(Client);

void Client::initialize()
{
    messageValue = generateValue();
    EV << messageValue << endl;
    WATCH(messageValue);
    MessageUpdate *msgUp = new MessageUpdate();
    msgUp->setValue(messageValue);
    int n = gateSize("gate$o");
    int index = n - 1;
    send(msgUp, "gate$o", index);
}

void Client::handleMessage(cMessage *msg)
{
    MessageUpdate *msgUp = check_and_cast<MessageUpdate *>(msg);
    messageValue = generateValue();
    EV << messageValue << endl;
    msgUp->setValue(messageValue);

    int n = gateSize("gate$o");
    int index = n - 1;
    send(msgUp, "gate$o", index);
}

double Client::generateValue() {
    std::random_device rd;
    std::mt19937 generator(rd());
    double min = 0.0;
    double max = 100.0;
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}
