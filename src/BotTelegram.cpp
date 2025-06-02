#include "BotTelegram.h"

#include "TelegramSender.h"
#include "JsonWorker.h"

#include <thread>

BotTelegram::BotTelegram(std::string offset) : offset(offset)
{
    std::thread t(check_msg);
    t.detach();
}

void BotTelegram::check_msg()
{
    std::string id, data;
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(10));
        auto ptr = TelegramSender::get_instance();
        ptr->call(std::string(""), type_msg::read, std::string(offset));
        auto v = Json_worker::read("jq -r '.result[] | select(.message.text != null) | {text: .message.text, id: .message.from.id}' ../res/result_512291450.json");
        if(!v.empty())
        {
            size_t pos1 = v[0].find(":"), pos2 = v[1].find(":");
            id = v[0].substr(pos1+1);
            data = v[1].substr(pos2+1);   
            for(const auto& user : users){
                if(user->get_id() == id){
                    user->notify(data);
                    break;
                }
            }
        }
    }
}