#include <iostream>
#include <memory>
#include <array>

#include "TelegramUser.h"

//"dbname=loganalyzer user=matsuess password=731177889232 host=localhost port=5432"

using namespace std;

int main(void)
{
    // array<char, 128> buffer;   
    // string result;

    // unique_ptr<FILE, decltype(&pclose)> pipe(popen("jq -r '.products[] | {name, regular: .prices.regular}' ../res/products.json", "r"), pclose);

    // while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
    //     result += buffer.data();
    // }

    // cout << result << '\n';

    // cout << launch_script_WO() << '\n';

    TelegramUser user("");

    user.add_in_list("Mollis");
    user.notify("Mollis");

    return 0;
}