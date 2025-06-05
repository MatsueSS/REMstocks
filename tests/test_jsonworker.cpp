#include <iostream>
#include "JsonWorker.h"

#include <fstream>

//, regular: .prices.regular

int main(void)
{
    auto res1 = Json_worker::read("jq -r '.products[] | {name}' ../res/products1.json", type_json::products);
    std::ofstream file("../res/result_test_json_worker.txt");
    file << "Result command-type with products: jq -r '.products[] | {name}' ../res/products.json:\n";
    for(const auto& obj : res1)
        file << '\t' << obj << '\n';

    auto res2 = Json_worker::read("jq -r '.result[] | select(.message.text != null) | {text: .message.text, id: .message.from.id}' ../res/result_512291452.json", type_json::message);

    file << "Result command-type with message:\n";
    file << '\t' << res2[1] << ' ' << res2[2] << '\n';

    return 0;
}