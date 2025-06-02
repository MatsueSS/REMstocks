#ifndef _BOT_TELEGRAM_H_
#define _BOT_TELEGRAM_H_

#include "TelegramUser.h"
#include <vector>
#include <algorithm>
#include <memory>

class BotTelegram{
public:
    BotTelegram(std::string);

    template<typename Type>
    void notify_all(Type&&);

    void check_msg();

    template<typename Type>
    void add_user(Type&& id);

    template<typename Type>
    TelegramUser* find_user(Type&&);

private:
    std::vector<std::unique_ptr<TelegramUser>> users;
    std::string offset;
};

template<typename Type>
void BotTelegram::notify_all(Type&& t)
{
    for(const auto& user : users)
        user->notify(std::forward<Type>(t));
}

template<typename Type>
void BotTelegram::add_user(Type&& id)
{
    users.emplace_back(std::make_unique<TelegramUser>(std::forward<Type>(id)));
}

template<typename Type>
TelegramUser* BotTelegram::find_user(Type&& t)
{
    auto it = std::find_if(users.begin(), users.end(), [&](const std::unique_ptr<TelegramUser>& obj){return obj->get_id() == t;});
    return it->get();
}

#endif //_BOT_TELEGRAM_H_