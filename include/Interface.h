#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <memory>

#include "BotTelegram.h"

class Interface{
public:
    Interface(std::string);

    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;

    void start();

private:
    std::unique_ptr<BotTelegram> bot;
    std::unordered_set<std::string> lovely_product;

    bool control_date();
};

#endif //_INTERFACE_H_