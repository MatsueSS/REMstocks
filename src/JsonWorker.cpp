#include "JsonWorker.h"

#include <array>
#include <memory>
#include <string>
#include <iostream>

std::vector<std::string> Json_worker::read(std::string query, type_json type)
{
    std::array<char, 128> buffer;   
    std::string str;

    std::vector<std::string> result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(query.c_str(), "r"), pclose);

    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
        switch(type){
            case type_json::products:
                result.push_back(Json_worker::erase_for_products(std::string(buffer.data())));
                break;
            case type_json::message:
                result.push_back(Json_worker::erase_for_messages(std::string(buffer.data())));
                break;
            default:
                break;
        }
    }

    return result;
}

std::string Json_worker::erase_for_products(std::string&& str)
{
    size_t pos = str.find(":");
    if(pos != std::string::npos){
        size_t elpos = str.rfind("\"");
        str = str.substr(pos+3, str.size()-10);
        str = str.substr(0, elpos-1);
    }

    return std::move(str);
}

std::string Json_worker::erase_for_messages(std::string&& str)
{
    size_t pos = str.find(":");
    if(pos != std::string::npos){
        str = str.substr(pos+2, str.size()-9);
        pos = str.find("\"");
        if(pos != std::string::npos){
            size_t elpos = str.rfind("\"");
            str = str.substr(pos+1, elpos-1);
        }
    }

    return std::move(str);
}