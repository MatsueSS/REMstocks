#include "Interface.h"

#include "PyLoader.h"
#include "json.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <future>
#include <iomanip>

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

    auto ymd = std::chrono::year{(int)year}/std::chrono::month{month}/std::chrono::day{day};
    auto current_date = get_date_now();

    std::chrono::sys_days new_date_days = std::chrono::sys_days{ymd} + std::chrono::days{7};
    std::chrono::sys_days my_date = std::chrono::sys_days{current_date};
    
    return my_date >= new_date_days;
}

std::chrono::year_month_day Interface::get_date_now() const
{
    auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
    auto current_date = std::chrono::year_month_day{today};
    return current_date;
}

bool Interface::start()
{
    if(control_date()){
        int code_result_script = PyLoader::script_load("bash -c 'python3 ../py_scripts/script_requests.py'");
        if(code_result_script == 1)
            PyLoader::script_load("bash -c 'python3 ../py_scripts/script_selenium.py'");
        
        PostgresDB db;
        db.connect("dbname=remstocks user=matsuess password=731177889232 host=localhost port=5432");

        std::ifstream file("../res/cards.json");
        nlohmann::json j;
        file >> j;

        std::string date = j["date"];

        for(const auto& card : j["cards"]){
            std::string name = card["name"];
            std::string str_price = card["price"];
            std::string str_sale = card["sale"];

            std::string price, sale;

            for(char c : str_price)
                if(isdigit(c))
                    price.push_back(c);

            for(char c : str_sale)
                if(isdigit(c))
                    sale.push_back(c);

            if(lovely_product.find(name) !=  lovely_product.end()){
                bot->notify_all(name);
            }

            db.execute("INSERT INTO cards (name, price, discount, date) VALUES($1, $2, $3, $4)", std::vector<std::string>{name, price, sale, date});
        }
        db.close();

        return 1;
    }

    else{
        std::cout << "Sales not update\n";
        
        return 0;
    }
}