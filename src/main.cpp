#include <iostream>
#include <memory>
#include <array>
#include <fstream>
#include <thread>

//"dbname=loganalyzer user=matsuess password=731177889232 host=localhost port=5432"
//"jq -r '.products[] | {name, regular: .prices.regular}' ../res/products.json"
//"jq -r '.result[] | select(.message.text != null) | {text: .message.text, id: .message.from.id}' ../res/result_512291448.json"

#include "Interface.h"

int main(void)
{
    // std::string id, token;
    // std::ifstream file("../.env");
    // file >> token >> id;

    // BotTelegram bot("512291454");
    // bot.add_user(id);

    // std::this_thread::sleep_for(std::chrono::seconds(15));

    // bot.notify_all("2. Mollis");

    ////////////
    
    Interface widget("512291452");
    widget.start();

    // std::vector<std::string> result = Json_worker::read("jq -r '.products[] | {name, regular: .prices.regular, discount: .prices.discount}' ../res/products1.json", type_json::products);

    // for(int i = 0; i < result.size(); i++)
    //     std::cout << result[i] << '\n';

    return 0;
}