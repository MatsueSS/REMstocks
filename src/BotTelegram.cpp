#include "BotTelegram.h"

#include "TelegramSender.h"
#include "JsonWorker.h"

#include <thread>
#include <iostream>

BotTelegram::BotTelegram(std::string offset) : offset(offset)
{
    std::thread t(&BotTelegram::check_msg, this);
    t.detach();
}

void BotTelegram::check_msg()
{
    std::string id, data;
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(10));
        auto ptr = TelegramSender::get_instance();
        ptr->call(std::string(""), type_msg::read, std::string(offset));
        auto v = Json_worker::read("jq -r '.result[] | select(.message.text != null) | {text: .message.text, id: .message.from.id}' ../res/result_"+ offset +".json");
        if(!v.empty())
        {
            size_t pos1 = v[1].find(":"), pos2 = v[2].find(":");
            data = v[1].substr(pos1+1);
            id = v[2].substr(pos2+2);
            id = id.substr(0, id.size()-1);  
            data = data.substr(2, data.size()-5);
            for(const auto& user : users){
                if(user->get_id() == id){
                    user->notify(data);
                    break;
                }
            }
        }
    }
}

BotTelegram::BotTelegram(BotTelegram&& obj) noexcept
{
    offset = std::move(obj.offset);
    users = std::move(obj.users);
}

BotTelegram& BotTelegram::operator=(BotTelegram&& obj) noexcept
{
    if(this == &obj)
        return *this;

    offset = std::move(obj.offset);
    users = std::move(obj.users);
    return *this;   
}

std::unordered_set<std::string> BotTelegram::get_like_product() const
{
    std::unordered_set<std::string> result;
    for(const auto& user : users){
        auto cards = user->get_cards();
        result.insert(std::make_move_iterator(cards.begin()), std::make_move_iterator(cards.end()));
    }
    return result;
}