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
    std::string id, token;
    std::ifstream file("../.env");
    file >> token >> id;

    TelegramUser user(std::move(id));

    std::ifstream nfile("../res/my_favourite_link.txt");
    while(getline(nfile, token)){
        user.add_card(token);
    }

    Interface widget("512291454");
    widget.add_user(std::move(user));
    
    widget.start();

    return 0;
}