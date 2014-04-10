/**
  * @file networkmanager.h
  * @author bsfmig
  * @date 2013.12.3
  */

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "commondefinitions.h"

class NetworkManager
{
public:
    NetworkManager();
    ~NetworkManager();

    static NetworkManager* getInstance();
    void startListening();
    void signalHandler();

private:
    bool initializeNetwork(int port=SERVERPORT);
    void asyncListener();

    static NetworkManager instance;
    int serverSock,clientSock;
    sockaddr_in servAddr;

    bool acceptConnection(messageHeader* Header);
    
    //A desine flaw!
    //This string is used by accceptImageData() to ensure which label it will save image to.
    std::string labelName;

    void dispatchMessage(messageHeader* Header);
    void messageEcho();

    //Methods related to label processing.
    void defineLabel(int labelNameLength);
    void acceptImageData(std::string labelName, unsigned long int imageSize);

};

#endif // NETWORKMANAGER_H
