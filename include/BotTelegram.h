#ifndef _BOT_TELEGRAM_H_
#define _BOT_TELEGRAM_H_

#include "TelegramUser.h"

#include <memory>
#include <vector>

class BotTelegram{
public:
    void add_sub(std::unique_ptr<Observer>);
    
    void analyze_sales(std::unordered_set<std::string>);

private:
    std::vector<std::unique_ptr<Observer>> subscribers;
};

#endif //_BOT_TELEGRAM_H_