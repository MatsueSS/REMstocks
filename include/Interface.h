#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "BotTelegram.h"
#include "JsonWorker.h"
#include "PostgresDB.h"

#include <memory>
#include <fstream>
#include <chrono>

class Interface{
public:
    Interface(std::string);

    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;

    void start();

private:
    std::unique_ptr<BotTelegram> bot;
    std::unordered_set<std::string> lovely_product;

    bool control_date();

    std::chrono::year_month_day get_date_now() const;
};

#endif //_INTERFACE_H_