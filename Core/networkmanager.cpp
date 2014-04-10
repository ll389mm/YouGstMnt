#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <exception>

#include "networkmanager.h"
#include "labelmanager.h"
#include "commondefinitions.h"

static const int MAXCONNECTIONS = 100;

NetworkManager NetworkManager::instance;

NetworkManager::NetworkManager()
{
    if(initializeNetwork()==false)
        std::cout<<"NetworkManager initialize failed"<<std::endl;
    else
        std::cout<<"NetworkManager initialized"<<std::endl;
}

NetworkManager* NetworkManager::getInstance()
{
    return &instance;
}

NetworkManager::~NetworkManager()
{
    close(serverSock);
    std::cout<<"Closing connection and destructing NetworkManager"<<std::endl;
}

bool NetworkManager::initializeNetwork(int port)
{
    in_port_t servPort=port;
    //Create socket.
    serverSock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (serverSock<0)
        return false;
    //Create sockaddr struct.
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port=htons(servPort);
    //Bind port.
    if (bind(serverSock,(sockaddr*)&servAddr,sizeof(servAddr))<0)
        return false;
    //Start listening.
    if (listen(serverSock,MAXCONNECTIONS)<0)
        return false;
    if (fcntl(serverSock,F_SETOWN,getpid())<0) //attempt to set signal listener to us
        return false;
    if (fcntl(serverSock,F_SETFL,O_NONBLOCK|FASYNC)<0)//attempt to initialize nonblocking io
        return false;
    return true;
}

void NetworkManager::startListening()
{
    messageHeader* Header=new messageHeader;
    endloopFlag=0;//break-out condition for signal processing
    while(endloopFlag==0)
    {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLength=sizeof(clientAddr);
        //Accept connection. It will block itself until a connection comes in.
        clientSock=accept(serverSock,(sockaddr*)&clientAddr,&clientAddrLength);
        if (clientSock<0)
        {
            std::cout<<"Error opening net socket for dispatching"<<std::endl;
            break;
        }
        std::cout<<"Socket "<<serverSock<<" accepted.\n";
        FILE* inBuffer=fdopen(serverSock,"r+");
        if (!inBuffer)
        {
            std::cout<<"Error opening input buffer for dispatching"<<std::endl;
            break;
        }
        if (acceptConnection(Header))
            dispatchMessage(Header);
        ::puts(".");
    }
}

bool NetworkManager::acceptConnection(messageHeader* Header)
{

    unsigned int numberOfBytesReceived=0;
    while (numberOfBytesReceived<sizeof(messageHeader))
    {
        int currentReceive=recv(clientSock,Header,sizeof(messageHeader),0);
        std::cout<<"Expected "<<sizeof(messageHeader)<<" bytes."<<std::endl;
        std::cout<<"Received "<<currentReceive<<" bytes."<<std::endl;
        if (currentReceive==-1)
        {
            std::cout<<"Error receiving"<<std::endl;
            break;
        }
        numberOfBytesReceived+=currentReceive;
    }

    return true;
}


void NetworkManager::dispatchMessage(messageHeader* Header)
{
    std::cout<<Header->version<<std::endl;
    std::cout<<Header->operand<<std::endl;
    std::cout<<Header->length<<std::endl;
    if (Header->version!=VERSION)
        std::cout<<"Version mismatch at"<<Header->version<<" Version"<<std::endl;
    switch (Header->operand)
    {
        case CONNECTION_ECHO:
            messageEcho();
            break;
        case DEFINE_LABEL:
            defineLabel(Header->length);
            break;
        case SEND_LABEL_SAMPLE_IMAGE:
            acceptImageData(labelName, Header->length);
            break;
    }
}

//Below are methods that process message dispatched by dispatchMessage()
void NetworkManager::messageEcho()
{
    int* sendBuf=new int[1];
    sendBuf[0]=1;
    if (send(clientSock,sendBuf,sizeof(sendBuf),0)<0)
        std::cout<<"Echo message send failed.\n";
    std::cout<<"Echo message sent.\n";
    delete sendBuf;
    sendBuf=NULL;
    return;
}

//Below are methods related to label processing.
void NetworkManager::defineLabel(int labelNameLength)
{
    char* name=new char[labelNameLength];
    int* sendBuf=new int[1];

    unsigned int numberOfBytesReceived=0;
    while (numberOfBytesReceived<sizeof(name))
    {
        int currentReceive=recv(clientSock,name,sizeof(name)-numberOfBytesReceived,0);
        if (currentReceive==-1)
        {
            std::cout<<"Error receiving"<<std::endl;
            break;
        }
        numberOfBytesReceived+=currentReceive;
    }

    labelName=std::string(name);
    LabelManager* lm=LabelManager::getInstance();
    Label newLabel=Label(name,name);//relative path used

    if(lm->addLabel(newLabel)!=0)
    {
        std::cout<<"Error adding label\n";
        delete name;
        delete sendBuf;
        return;
    }

    std::cout<<"Label "<<labelName<<" added\n";
    messageEcho();
    delete name;
    delete sendBuf;
    return;
}

void NetworkManager::acceptImageData(std::string labelName, unsigned long int imageSize)
{
    unsigned char* Data=new unsigned char[imageSize];
    Label* targetLabel;

    //Initialize related label.
    LabelManager* lm = LabelManager::getInstance();
    if (lm->ifLabelExistsByName(labelName))
        targetLabel = lm->getLabelByName(labelName);
    else
    {
        std::cout<<"Label not existant\n";
        delete Data;
        return;
    }

    //Fill the buffer using network data.
    unsigned int numberOfBytesReceived=0;
    while (numberOfBytesReceived<imageSize)
    {
        int currentReceive=recv(clientSock,Data+numberOfBytesReceived,imageSize-numberOfBytesReceived,0);
        if (currentReceive==-1)
        {
            std::cout<<"Error receiving"<<std::endl;
            break;
        }
        numberOfBytesReceived+=currentReceive;
    }

    //---------------------------------------------------------------------//

    //Fill the buffer into a file.

    //Establish filename using current time.
    long int currentTime = ::time(NULL);
    std::string fileName;
    std::stringstream ss(fileName);
    ss << currentTime;
    fileName+=".jpg";
    std::cout<<"Filename is "<<fileName<<" \n";

    //Setup ofstream.
    fileName = targetLabel->getImageDirectory() + "/" + fileName;
    std::ofstream out(fileName.c_str());
    if (!out)
    {
        std::cout<<"Error opening file for saving.\n";
        delete Data;
        return;
    }

    out.write(reinterpret_cast<char *>(Data), imageSize);

    //Cleanup.
    out.close();
    std::cout<<imageSize<<" bytes written.\n";
    delete Data;
    return;
}
