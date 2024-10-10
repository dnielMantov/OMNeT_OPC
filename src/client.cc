#include <omnetpp.h>
#include "opcserver.h"

using namespace omnetpp;

class Client : public cSimpleModule
{
//    private:
//        OpcUa::BaseDataVariableType* pVariable;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
//        virtual OpcMessage *generateMessage();
};

Define_Module(Client);

void Client::initialize()
{
    cMessage *msg = new cMessage("newMessage");
    send(msg, "out");
}

void Client::handleMessage(cMessage *msg)
{
    send(msg, "out");
}

//OpcMessage *Client::generateMessage() {
//    std::string conteudo = "Message: ???";
//
//    OpcMessage *message = new OpcMessage();
//    message->setConteudo(conteudo.c_str());
//    return message;
//}
