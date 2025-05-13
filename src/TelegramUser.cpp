#include "TelegramUser.h"

#include <utility>
#include <curl/curl.h>

Observer::Observer(std::string val) : id(std::move(val))
{}

TelegramUser::TelegramUser(std::string val) : Observer(std::move(val))
{}

void TelegramUser::add_in_list(std::string val)
{
    list_needed.emplace(val);
}

void TelegramUser::del_in_list(std::string val)
{
    list_needed.erase(std::move(val));
}

void TelegramUser::notify(std::string sale)
{
    if(list_needed.find(sale) != list_needed.end()){
        send_message(sale);
    }
}

void TelegramUser::send_message(std::string sale)
{
    std::string token = "";
    std::string url = "https://api.telegram.org/bot" + token + "/sendMessage";
    char* esc = curl_easy_escape(nullptr, sale.c_str(), 0);
    std::string post_fields = "chat_id=" + id + "&text=" + esc;
    curl_free(esc);

    CURL *curl = curl_easy_init();
    if(curl){
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }
}