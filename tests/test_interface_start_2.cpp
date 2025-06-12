#include "Interface.h"

#include <iostream>

int main(void)
{
    std::string id, token;
    std::ifstream file("../.env");
    file >> token >> id;

    TelegramUser user(id);

    Interface widget("512291454");
    widget.add_user(std::move(user));

    std::ifstream nfile("../res/my_favourite_link.txt");
    while(getline(nfile, token)){
        widget.add_card_for_concrete_user(id, token);
    }
    
    widget.start();

    while(true){
        
    }
}