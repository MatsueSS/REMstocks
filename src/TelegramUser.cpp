#include "TelegramUser.h"

#include <thread>

#include "TelegramSender.h"

TelegramUser::TelegramUser(std::string id) : id(id) {}

void TelegramUser::notify(std::string sale)
{
    auto ptr = TelegramSender::get_instance();
    ptr->call(id, type_msg::send, sale);
}

std::string TelegramUser::get_id() const
{
    return id;
}