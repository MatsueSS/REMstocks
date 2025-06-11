#include "Interface.h"

int main(void)
{
    PostgresDB db;
    db.connect("dbname=remstocks user=matsuess password=731177889232 host=localhost port=5432");
    db.execute("DROP TABLE cards;", std::vector<int>{});
    db.execute("CREATE TABLE cards (id SERIAL PRIMARY KEY, name VARCHAR(64) NOT NULL, price SMALLINT NOT NULL, discount SMALLINT, date DATE);", std::vector<int>{});
    db.close();

    Interface interface("512291452");
    interface.start();
}