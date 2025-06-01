#ifndef _TELEGRAM_SENDER_H_
#define _TELEGRAM_SENDER_H_

#include <future>

enum class type_msg{
    read, send
};

class TelegramSender{
public:
    TelegramSender(const TelegramSender&) = delete;
    TelegramSender& operator=(const TelegramSender&) = delete;

    static TelegramSender get_instance();
    static void destroy();

    template<typename Data, typename Type>
    std::future<std::string> call(Data&&, Data&&, Type&&, Data&&);

private:
    static TelegramSender* instance;

    TelegramSender() = default;
    std::string query(std::string, std::string, type_msg, std::string);
};

#endif // _TELEGRAM_SENDER_H_
