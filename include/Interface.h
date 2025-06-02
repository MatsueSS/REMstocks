#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <memory>

class BotTelegram;

class Interface{
public:
    Interface(std::string);

    void start();

private:
    std::unique_ptr<BotTelegram> bot;
    
};

#endif //_INTERFACE_H_