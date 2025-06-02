#include "TelegramUser.h"

#include <thread>
#include <iostream>

#include "TelegramSender.h"

TelegramUser::TelegramUser(std::string id) : id(id) {}

void TelegramUser::notify(std::string sale)
{
    int val = sale[0] - '0';
    sale = sale.substr(3);
    switch(val){
        case 1: //add card
            add_card(sale);
            break;
        case 2: //send sales
        {
            auto ptr = TelegramSender::get_instance();
            if(cards.find(sale) != cards.end())
                ptr->call(id, type_msg::send, sale);
            break;
        }
        case 3: //make forecast
            break;
        default:
            break;
    }
}

std::string TelegramUser::get_id() const
{
    return id;
}

TelegramUser::TelegramUser(TelegramUser&& obj) noexcept
{
    cards = std::move(obj.cards);
    id = std::move(obj.id);
}

TelegramUser& TelegramUser::operator=(TelegramUser&& obj) noexcept
{
    if(this == &obj)
        return *this;

    cards = std::move(obj.cards);
    id = std::move(obj.id);
    return *this;
}