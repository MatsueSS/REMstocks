#include <iostream>
#include <memory>
#include <array>
#include <fstream>

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

    BotTelegram tg("512291448");
    tg.add_user(id);
    tg.find_user(id)->add_card("Mollis");
    tg.notify_all("Mollis");
    std::cout << id << '\n';

    return 0;
}