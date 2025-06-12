#include "TelegramUser.h"

#include <thread>
#include <iostream>
#include <fstream>

#include "json.hpp"
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
        case 4: { //want sales
            std::ifstream file("../res/cards.json");
            nlohmann::json json;
            file >> json;

            for(const auto& obj : json["cards"]){
                std::string name = obj["name"];

                if(cards.find(name) != cards.end()){
                    auto ptr = TelegramSender::get_instance();
                    ptr->call(id, type_msg::send, name);
                }
            }

            break;
        }
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

std::unordered_set<std::string> TelegramUser::get_cards() const
{
    return cards;
}