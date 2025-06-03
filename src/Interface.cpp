#include "Interface.h"

#include "PyLoader.h"

#include <iostream>
#include <string>

Interface::Interface(std::string offset)
{
    bot = std::make_unique<BotTelegram>(offset);

    lovely_product = bot->get_like_product();
}

void Interface::start()
{
    while(true){
        if(PyLoader::script_load("bash -c 'python3 ../py_scripts/pars_script.py'") == 1){
            std::cout << "403 error\n";
            std::terminate();
        }
        
    }
}