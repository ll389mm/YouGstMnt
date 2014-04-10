#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
public:
    Command(const std::string &n, int c);

    std::string getName();

    unsigned char getCode();

    AbstractCommandHandler *commandHandler();

    void setCommandHandler(AbstractCommandHandler *cmdHdl);

    int frontCounts();

    AbstractInterceptor *firstFront();

    int backCounts();

    AbstractInterceptor *firstBack();

private:
    const std::string name; const unsigned char code;
    AbstractCommandHandler *cmdHandler;
    int fc; AbstractInterceptor *ff;
    int bc; AbstractInterceptor *fb;
};

#endif // COMMAND_H
