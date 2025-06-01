#ifndef _TELEGRAM_SENDER_H_
#define _TELEGRAM_SENDER_H_

#include <future>

extern std::string token;

enum class type_msg{
    read, send
};

class TelegramSender{
public:
    TelegramSender(const TelegramSender&) = delete;
    TelegramSender& operator=(const TelegramSender&) = delete;

    static TelegramSender* get();
    static void destroy();
    
    template<typename Data, typename Type>
    std::future<std::string> call(Data&&, Data&&, Type&&, Data&&);

private:
    TelegramSender() = default;
    std::string query(std::string, std::string, type_msg, std::string);

    static TelegramSender* ptr;

    size_t writecallback(void*, size_t, size_t, void*);
};

template<typename Data, typename Type>
std::future<std::string> TelegramSender::call(Data&& token, Data&& id, Type&& type, Data&& data)
{
    return std::async(std::launch::async, &TelegramSender::query, this, std::forward<Data>(token), std::forward<Data>(id), std::forward<Type>(type), std::forward<Data>(data));
}

#endif //_TELEGRAM_SENDER_H_