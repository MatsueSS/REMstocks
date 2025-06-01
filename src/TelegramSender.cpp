#include "TelegramSender.h"

#include <fstream>
#include <curl/curl.h>

std::string token = "7866507385:AAHGy38IeJutSz7F_6VOqSs_tZVO51zHH9A";

TelegramSender* TelegramSender::ptr = nullptr;

TelegramSender* TelegramSender::get()
{
    if(ptr)
        return ptr;

    ptr = new TelegramSender();
    return ptr;
}

void TelegramSender::destroy()
{
    delete ptr;
    ptr = nullptr;
}

size_t TelegramSender::writecallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    std::ofstream* out = static_cast<std::ofstream*>(userp);
    size_t totalSize = size * nmemb;
    out->write(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string TelegramSender::query(std::string token, std::string id, type_msg type, std::string data)
{
    CURL *curl = curl_easy_init();
    if(!curl){
        return "";
    }
    CURLcode res;
    switch (type)
    {
    case type_msg::send:
    {
        std::string url = "https://api.telegram.org/bot" + token + "/sendMessage";
        char* esc = curl_easy_escape(nullptr, data.c_str(), 0);
        std::string post_fields = "chat_id=" + id + "&text=" + esc;
        curl_free(esc);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        res = curl_easy_perform(curl);
        break;
    }
    case type_msg::read:
    {
        std::string url = "https://api.telegram.org/bot" + token + "/getUpdates?timeout=10&offset=" + data;
        std::ofstream file("../res/tg_api_"+id+"_result.json");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &TelegramSender::writecallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
        res = curl_easy_perform(curl);
        break;
    }
    }

    curl_easy_cleanup(curl);
}