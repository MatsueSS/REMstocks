#include <iostream>
#include <memory>
#include <array>
#include <fstream>

//"dbname=loganalyzer user=matsuess password=731177889232 host=localhost port=5432"

using namespace std;

#include <curl/curl.h>

#include "TelegramSender.h"

// size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
// {
//     std::string* response = static_cast<std::string*>(userp);
//     size_t total_size = size*nmemb;
//     response->append(static_cast<char*>(contents), total_size);
//     return total_size;
// }

int main(void)
{
    // array<char, 128> buffer;   
    // string result;

    // unique_ptr<FILE, decltype(&pclose)> pipe(popen("jq -r '.products[] | {name, regular: .prices.regular}' ../res/products.json", "r"), pclose);

    // while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
    //     result += buffer.data();
    // }

    // cout << result << '\n';

    array<char, 128> buffer;   
    string result;

    unique_ptr<FILE, decltype(&pclose)> pipe(popen("jq -r '.result[] | select(.message.text != null) | {text: .message.text, id: .message.from.id}' ../res/result_512291448.json", "r"), pclose);

    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
        result += buffer.data();
    }

    cout << result << '\n';

    // TelegramSender* ptr = TelegramSender::get_instance();
    // std::ifstream file("../.env");
    // std::string id, t1;
    // file >> t1 >> id;
    // ptr->call(move(id), type_msg::read, string("512291450"));

    return 0;
}