#ifndef _TELEGRAM_USER_H_
#define _TELEGRAM_USER_H_

#include <string>
#include <unordered_set>

class TelegramUser{
public:
    TelegramUser(std::string id);

    TelegramUser(const TelegramUser&) = delete;
    TelegramUser& operator=(const TelegramUser&) = delete;

    TelegramUser(TelegramUser&&) noexcept;
    TelegramUser& operator=(TelegramUser&&) noexcept;

    void notify(std::string);
    std::string get_id() const;

    template<typename Type>
    void add_card(Type&&);

    template<typename Type>
    void del_card(Type&&);

    std::unordered_set<std::string> get_cards() const;

private:
    std::string id;
    std::unordered_set<std::string> cards;

};

template<typename Type>
void TelegramUser::add_card(Type&& t)
{
    cards.emplace(std::forward<Type>(t));
}

template<typename Type>
void TelegramUser::del_card(Type&& t)
{
    cards.erase(std::forward<Type>(t));
}

#endif //_TELEGRAM_USER_H_