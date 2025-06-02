#include "TelegramUser.h"

#include <thread>

#include "TelegramSender.h"

Observer::Observer(std::string id) : id(id) {}

TelegramUser::TelegramUser(std::string id) : Observer(std::move(id)) {}

void TelegramUser::notify(std::string sale)
{
    auto ptr = TelegramSender::get_instance();
    ptr->call(id, type_msg::send, sale);
}

std::string Observer::get_id() const
{
    return id;
}