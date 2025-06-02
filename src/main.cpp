#include <iostream>
#include <memory>
#include <array>
#include <fstream>
#include <thread>

//"dbname=loganalyzer user=matsuess password=731177889232 host=localhost port=5432"
//"jq -r '.products[] | {name, regular: .prices.regular}' ../res/products.json"
//"jq -r '.result[] | select(.message.text != null) | {text: .message.text, id: .message.from.id}' ../res/result_512291448.json"

#include "TelegramSender.h"
#include "JsonWorker.h"
#include "BotTelegram.h"

int main(void)
{
    std::string id, token;
    std::ifstream file("../.env");
    file >> token >> id;

    BotTelegram tg("512291451");
    tg.add_user(id);
    
    std::this_thread::sleep_for(std::chrono::seconds(15));
    tg.notify_all("2. Mollis");
    tg.notify_all("2. Филе");

    return 0;
}