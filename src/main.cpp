#include <iostream>
#include <memory>
#include <array>
#include <fstream>

//"dbname=loganalyzer user=matsuess password=731177889232 host=localhost port=5432"
//"jq -r '.products[] | {name, regular: .prices.regular}' ../res/products.json"
//"jq -r '.result[] | select(.message.text != null) | {text: .message.text, id: .message.from.id}' ../res/result_512291448.json"

#include "TelegramSender.h"
#include "JsonWorker.h"

int main(void)
{
    

    return 0;
}