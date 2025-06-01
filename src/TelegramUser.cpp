#include "TelegramUser.h"

#include "TelegramSender.h"

#include <utility>
#include <curl/curl.h>

Observer::Observer(std::string val) : id(std::move(val))
{}

TelegramUser::TelegramUser(std::string val) : Observer(std::move(val))
{}

void TelegramUser::add_in_list(std::string val)
{
    list_needed.emplace(val);
}

void TelegramUser::del_in_list(std::string val)
{
    list_needed.erase(std::move(val));
}

void TelegramUser::notify(std::string sale)
{
    if(list_needed.find(sale) != list_needed.end()){
        send_message(sale);
    }
}



void TelegramUser::send_message(std::string sale)
{
    TelegramSender* ptr = TelegramSender::get();
    auto fut = ptr->call(token, id, type_msg::send, sale);
    fut.get();
}