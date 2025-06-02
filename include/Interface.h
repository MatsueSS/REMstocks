#ifndef _INTERFACE_H_
#define _INTERFACE_H_

class BotTelegram;

class Interface{
public:
    Interface();

    void start();

private:
    BotTelegram* bot;
    
};

#endif //_INTERFACE_H_