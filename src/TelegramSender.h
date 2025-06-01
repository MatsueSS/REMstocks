#include "../include/TelegramSender.h"

#include <fstream>

TelegramSender::TelegramSender()
{
    std::ifstream file("../.env");
    file >> token;
}

TelegramSender* TelegramSender::get_instance()
{
    if(instance)
        return instance;

    instance = new TelegramSender();
}

void TelegramSender::destroy()
{
    delete instance;
}

