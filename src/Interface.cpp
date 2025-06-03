#include "Interface.h"

#include "BotTelegram.h"

#include <string>

Interface::Interface(std::string offset)
{
    bot = std::make_unique<BotTelegram>(offset);
}

void start()
{
    while(true){
        
    }
}