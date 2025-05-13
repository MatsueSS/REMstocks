#ifndef _TELEGRAM_USER_H_
#define _TELEGRAM_USER_H_

#include <unordered_set>
#include <string>

class Observer{
public:
    Observer(std::string id);

    virtual ~Observer() = default;
    virtual void notify(std::string) = 0;

protected:
    std::string id;

};

class TelegramUser : public Observer{
public:
    TelegramUser(std::string);

    virtual void notify(std::string) override;

    void add_in_list(std::string);
    void del_in_list(std::string);

private:
    std::unordered_set<std::string> list_needed;

    void send_message(std::string);

};

#endif //_TELEGRAM_USER_H_