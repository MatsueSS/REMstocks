#include <iostream>
#include "PostgresDB.h"

using namespace std;

int main(void)
{
    PostgresDB db;
    db.connect("dbname=loganalyzer user=matsuess password=731177889232 host=localhost port=5432");

    vector<vector<std::string>> result_query = db.fetch("SELECT * FROM data;", vector<std::string>{});

    for(int i = 0; i < result_query.size(); i++){
        for(int j = 0; j < result_query[0].size(); j++){
            cout << result_query[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << db.is_connect() << '\n';

    db.close();

    cout << db.is_connect() << '\n';

    db.close();

    return 0;
}