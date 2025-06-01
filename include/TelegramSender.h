#ifndef _TELEGRAM_SENDER_H_
#define _TELEGRAM_SENDER_H_

#include <future>
#include <string>

enum class type_msg{
    read, send
};

class TelegramSender{
public:
    TelegramSender(const TelegramSender&) = delete;
    TelegramSender& operator=(const TelegramSender&) = delete;

    static TelegramSender* get_instance();
    static void destroy();

    template<typename Data, typename Type>
    std::future<std::string> call(Data&&, Type&&, Data&&);

private:
    static TelegramSender* instance;
    std::string token;

    TelegramSender() = default;
    std::string query(std::string, type_msg, std::string);
};

template<typename Data, typename Type>
std::future<std::string> TelegramSender::call(Data&& id, Type&& type, Data&& msg)
{
    return std::async(std::launch::async, &TelegramSender::query, get(), std::forward<Data>(id), std::forward<Type>(type), std::forward<Data>(msg));
}

#endif // _TELEGRAM_SENDER_H_
