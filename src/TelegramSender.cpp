#include "TelegramSender.h"

#include <fstream>
#include <curl/curl.h>
#include <iostream>

TelegramSender* TelegramSender::instance = nullptr;

TelegramSender::TelegramSender()
{
    std::ifstream file("../.env");
    curl_global_init(CURL_GLOBAL_DEFAULT);
    file >> token;
}

TelegramSender* TelegramSender::get_instance()
{
    if(instance)
        return instance;

    instance = new TelegramSender();
    return instance;
}

void TelegramSender::destroy()
{
    delete instance;
}

size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
    std::ofstream* response = static_cast<std::ofstream*>(userp);
    size_t total_size = size*nmemb;
    response->write(static_cast<char*>(contents), total_size);
    return total_size;
}

std::string TelegramSender::query(std::string id, type_msg type, std::string data)
{
    std::string url = "https://api.telegram.org/bot" + token;
    switch(type){
        case type_msg::read:
        {
            url += "/getUpdates?offset=";
            url += data;
            std::ofstream file("../res/result_"+ data +".json");
            CURL* curl = curl_easy_init();
            if(curl){
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
                CURLcode res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }
            break;
        }
        case type_msg::send:
        {
            url += "/sendMessage";
            CURL* curl = curl_easy_init();
            if(curl){
                char *encoding = curl_easy_escape(curl, data.c_str(), data.length());
                std::string post_fileds = "chat_id="+id+"&text="+encoding;
                curl_free(encoding);
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fileds.c_str());
                CURLcode res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }
            break;
        }
    }
    return "";
}