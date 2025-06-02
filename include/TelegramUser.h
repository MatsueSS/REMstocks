#ifndef _TELEGRAM_USER_H_
#define _TELEGRAM_USER_H_

#include <string>

class Observer{
public:
    Observer(std::string id);

    virtual void notify(std::string) = 0;

    std::string get_id() const;

    virtual ~Observer() = default;
protected:
    std::string id;
};

class TelegramUser : public Observer{
public:
    TelegramUser(std::string id);

    void notify(std::string) override;

};

#endif //_TELEGRAM_USER_H_