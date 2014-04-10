#ifndef COMMONDEFINITIONS_H
#define COMMONDEFINITIONS_H

static int endloopFlag;

struct messageHeader{
    u_int8_t version;
    u_int8_t operand;
    u_int32_t length;
};

struct messageBody{

};

#define     VERSION 1
#define     SERVERPORT 52525

#define     EMPTYSTRING             ("")
#define     NULLPOINTER(type)       ((type*)0)
#define     NULLREFERENCE(type)     (*(NULLPOINTER(type)))

#define     BEGINEXTERNC            extern "C" {
#define     ENDEXTERNC              }
#define     EXTERNCMODIFIER         extern "C"

//Operands used in NetworkManager's command dispatching. Subject to change!
#define CONNECTION_ECHO 1 //Client: "Ping" request.
#define DEFINE_LABEL 2 //Client: Define a new label
#define SEND_LABEL_SAMPLE_IMAGE 3 //Client: Send an image as a sample of a label

#endif // COMMONDEFINITIONS_H
