#include "PostgresDB.h"

#include <iostream>
#include <fstream>

int main(void)
{
    std::string name = "dbname=loganalyzer user=matsuess password=731177889232 host=localhost port=5432";
    PostgresDB db;
    db.connect(std::move(name));
    
    std::ofstream file("../res/result_test_db.txt");
    file << "Open result: " << db.is_connect() << '\n';

    db.close();
    file << "Exit result: " << db.is_connect() << '\n';

    db.connect(std::move(name));
    file << "Open result: " << db.is_connect() << '\n';

    bool result = db.execute("INSERT INTO data (resourse_name, password, user_id) VALUES ($1, $2, $3);", std::vector<std::string>{"test", "psw", "2"});
    file << "Result query insert: " << result << '\n';

    auto vec = db.fetch("SELECT * FROM data;", std::vector<std::string>{});
    file << "Result fetch-command SELECT * FROM data;:" << '\n';
    for(const auto& obj : vec){
        file << '\t';
        for(const auto& other : obj)
            file << other << ' ';
        file << '\n';
    }

    return 0;
}