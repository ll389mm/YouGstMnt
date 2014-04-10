#include <iostream>

//Used to terminate the program by Ctrl-C key stroke.
#include <csignal> //Unix only! Need to be adapted to Win32 environment later.
#include <csetjmp>

#include "implementationmanager.h"
#include "labelmanager.h"
#include "modelmanager.h"
#include "classifiermanager.h"
#include "networkmanager.h"
#include "commondefinitions.h"

void callSigInt(int);

int main()
{
    std::cout<<"SeeingEye Server Starting..."<<std::endl;
    ImplementationManager* im=ImplementationManager::getInstance();
    NetworkManager* nm=NetworkManager::getInstance();
    if(signal(SIGINT|SIGPIPE|SIGALRM,callSigInt)==SIG_ERR)
    {
        std::cout<<"Error in initialization\n";
        return -1;
    }
    else
        std::cout<<"Signal Registered."<<std::endl;
    nm->startListening();
    return 0;
}

void callSigInt(int signo)
{
    std::cout<<"Signal "<<signo<<" caught."<<std::endl;
    endloopFlag=1;
    NetworkManager* nm=NetworkManager::getInstance();
    nm->signalHandler();
}
