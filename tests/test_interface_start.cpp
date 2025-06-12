#include "Interface.h"

int main(void)
{
    PostgresDB db;
    db.connect("dbname=remstocks user=matsuess password=731177889232 host=localhost port=5432");
    db.execute("DROP TABLE cards;", std::vector<std::string>{});
    db.execute("CREATE TABLE cards (id SERIAL PRIMARY KEY, name TEXT NOT NULL, price SMALLINT NOT NULL, discount SMALLINT, date DATE);", std::vector<std::string>{});
    db.close();

    Interface interface("512291452");
    std::ofstream file("../res/result_test_interface_start.txt", std::ios::app);

    file << "Result of usual 1:" << interface.start() << '\n';

    auto res = db.fetch("SELECT * FROM cards;", std::vector<std::string>{});
    for(const auto& obj : res)
        for(const auto& pbj : obj){
            file << pbj << '\n';
        }

    return 0;
}