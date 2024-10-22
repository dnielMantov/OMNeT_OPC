#include "uaplatformlayer.h"
#include "opcserver.h"
#include "shutdown.h"

#if SUPPORT_XML_PARSER
    #include "xmldocument.h"
#endif

#include <omnetpp.h>
#include "opcserver.h"
#include "messageUpdate_m.h"

using namespace omnetpp;

class Server : public cSimpleModule
{
    private:
        OpcServer* pServer;
        OpcUa::BaseDataVariableType* pVariable;

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Server);

void Server::initialize()
{
    char* szAppPath = getAppPath();
    int ret = 0;

    #if SUPPORT_XML_PARSER
        UaXmlDocument::initParser();
    #endif
    
    ret = UaPlatformLayer::init();

    if (ret == 0) {
        // Create configuration file name
        UaString sConfigFileName(szAppPath);

        #if SUPPORT_XML_PARSER
            sConfigFileName += "/ServerConfig.xml";
        #else
            sConfigFileName += "/ServerConfig.ini";
        #endif

        // Create and initialize server object
        pServer = new OpcServer;
        ret = pServer->setServerConfig(sConfigFileName, szAppPath);
        if (ret != 0) {
            printf("Error setting OPC server configuration: %d\n", ret);
            EV << "Error setting OPC server configuration: " + std::to_string(ret) << std::endl;
        } 
        
        ret = pServer->start();
        if (ret != 0) {
            printf("Error starting OPC server: %d\n", ret);
            EV << "Error starting OPC server: " + std::to_string(ret) << std::endl;
        } else {
            printf("OPC server started successfully: %d\n", ret);
            EV << "OPC server started successfully: " + std::to_string(ret) << std::endl;
        }

        if (ret == 0) {
            NodeManagerConfig* pNodeConfig = pServer->getDefaultNodeManager();

            // Create a variable node with a string data type
            UaVariant defaultValue;
            defaultValue.setDouble(0);
            pVariable = new OpcUa::BaseDataVariableType(
                UaNodeId("Message", pNodeConfig->getNameSpaceIndex()), // NodeId of the node with string identifier "HelloWorld" and the namespace index of the default node manager which is 1
                "Message",  // Name of the node used for display name and browse name
                pNodeConfig->getNameSpaceIndex(), // The same namespace index is also used for the browse name
                defaultValue, // Setting the default value and the data type of the variable
                OpcUa_AccessLevels_CurrentReadOrWrite, // Setting the access level to read only
                pNodeConfig); // The node manager config interface used for this node

            // Add the node to the node manager using the objects folder as source node and the reference type HasComponent
            pNodeConfig->addNodeAndReference(UaNodeId(OpcUaId_ObjectsFolder, 0), pVariable, OpcUaId_HasComponent);
        }
    }
}

void Server::handleMessage(cMessage *msg)
{
    MessageUpdate *msgUp = check_and_cast<MessageUpdate *>(msg);

    UaVariant newValue;
    newValue.setDouble(msgUp->getValue());

    UaDataValue dataValue;
    dataValue.setValue(newValue, OpcUa_False, OpcUa_True);

    pVariable->setValue(NULL, dataValue, OpcUa_False);

    send(msgUp, "gate$o");
}