#include "TelegramUser.h"

#include <iostream>
#include <fstream>

int main(void)
{
    std::string id, token;
    std::ifstream file("../.env");
    file >> token >> id;

    TelegramUser user(id);
    user.add_card("Mollis");
    user.add_card("Филе");
    auto cards = user.get_cards();
    std::ofstream nfile("../res/result_test_telegramuser.txt");
    nfile << "Result of added in cards: ";
    for(auto iter = cards.begin(); iter != cards.end(); iter++)
        nfile << *iter << ' '; 
    nfile << '\n';
    user.notify("2. Mollis");
    nfile << "Make notify\n";
    user.notify("1. Морковь");
    nfile << "Added a new note with notify\n";
    nfile << "Result of added in cards: ";
    cards = user.get_cards();
    for(auto iter = cards.begin(); iter != cards.end(); iter++)
        nfile << *iter << ' ';

    nfile << "User id " << user.get_id();

    return 0;
}