#include "Interface.h"

#include "PyLoader.h"
#include "JsonWorker.h"

#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <thread>

Interface::Interface(std::string offset)
{
    bot = std::make_unique<BotTelegram>(offset);

    lovely_product = bot->get_like_product();
}

bool Interface::control_date()
{
    auto res = Json_worker::read("jq -r '.date' ../res/cards.json", type_json::products);
    std::string date_str = res[0];
    std::istringstream ss(date_str);
    char delimiter;
    unsigned int day, month, year;
    ss >> day >> delimiter;
    if(delimiter != '-' || ss.fail())
        return false;
    ss >> month >> delimiter;
    if(delimiter != '-' || ss.fail())
        return false;
    ss >> year;
    if(ss.fail())
        return false;

    auto ymd = std::chrono::year{year}/std::chrono::month{month}/std::chrono::day{day};
    auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
    auto current_date = std::chrono::year_month_day{today};

    std::chrono::sys_days new_date_days = std::chrono::sys_days{ymd} + std::chrono::days{7};
    std::chrono::sys_days my_date = std::chrono::sys_days{current_date};
    
    return my_date >= new_date_days;
}

void Interface::start()
{
    while(true){
        if(control_date()){
            int code_result_script = PyLoader::script_load("bash -c 'python3 ../py_scripts/script_requests.py'");
            if(code_result_script == 1)
                PyLoader::script_load("bash -c 'python3 ../py_scripts/script_selenium.py'");
        }
        else{
            std::cout << "Sales not update\n";
        }
        
    }
}