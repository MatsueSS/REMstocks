#ifndef _BOT_TELEGRAM_H_
#define _BOT_TELEGRAM_H_

#include "TelegramUser.h"
#include <vector>

class BotTelegram{
public:
    BotTelegram(std::string);

    void notify_all();

    void check_msg();

private:
    std::vector<Observer*> users;
    std::string offset;
};

#endif _BOT_TELEGRAM_H_