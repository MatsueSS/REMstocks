#include <iostream>
#include <memory>
#include <array>
#include <fstream>

//"dbname=loganalyzer user=matsuess password=731177889232 host=localhost port=5432"
//"jq -r '.products[] | {name, regular: .prices.regular}' ../res/products.json"
//"jq -r '.result[] | select(.message.text != null) | {text: .message.text, id: .message.from.id}' ../res/result_512291448.json"

#include "TelegramSender.h"
#include "JsonWorker.h"

int main(void)
{
    // auto ptr = TelegramSender::get_instance();
    // ptr->call(std::string(""), type_msg::read, std::string("512291448"));
    auto res = Json_worker::read("jq -r '.result[] | select(.message.text != null) | {text: .message.text, id: .message.from.id}' ../res/result_512291448.json");
    for(std::string s : res)
        std::cout << s;

    for(const auto& line : res){
        size_t pos = line.find(":");
        if(pos != std::string::npos){
            std::string title = line.substr(0, pos);
            std::string data = line.substr(pos+1);
        }
    }

    return 0;
}