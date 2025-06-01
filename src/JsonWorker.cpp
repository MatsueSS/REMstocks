#include "JsonWorker.h"

#include <array>
#include <memory>

std::vector<std::string> Json_worker::read(std::string query)
{
    std::array<char, 128> buffer;   
    std::string str;

    std::vector<std::string> result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(query.c_str(), "r"), pclose);

    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
        result.push_back(buffer.data());
    }

    return result;
}