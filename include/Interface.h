#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "BotTelegram.h"
#include "JsonWorker.h"
#include "PostgresDB.h"

#include <memory>
#include <fstream>
#include <chrono>

class Interface{
public:
    Interface(std::string);

    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;

    bool start();

    template<typename type>
    void add_user(type&&);

    template<typename type>
    void add_card_for_concrete_user(type&& user_id, type&& card);

private:
    std::unique_ptr<BotTelegram> bot;

    bool control_date();

    std::chrono::year_month_day get_date_now() const;
};

template<typename type>
void Interface::add_user(type&& obj)
{
    bot->add_user(std::forward<type>(obj));
}

template<typename type>
void Interface::add_card_for_concrete_user(type&& user_id, type&& card)
{
    bot->find_user(std::forward<type>(user_id))->add_card(std::forward<type>(card));
}

#endif //_INTERFACE_H_