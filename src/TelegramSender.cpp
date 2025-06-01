#include "TelegramSender.h"

#include <fstream>
#include <curl/curl.h>

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

std::string TelegramSender::query(std::string id, type_msg type, std::string data)
{
    std::string response = "";
    std::string url = "https://api.telegram.org/bot" + token;
    switch(type){
        case type_msg::read:
        {
            url += "/getUpdates";
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
        }
    }
    return response;
}