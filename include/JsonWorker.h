#ifndef _JSON_WORKER_H_
#define _JSON_WORKER_H_

#include <vector>
#include <string>

enum class type_json{
    products, message
};

class Json_worker{
public:
    static std::vector<std::string> read(std::string, type_json);

private:
    static std::string erase_for_products(std::string&&);
    static std::string erase_for_messages(std::string&&);
};

#endif //_JSON_WORKER_H_