#ifndef _POSTGRES_DB_H_
#define _POSTGRES_DB_H_

//In future std::function can will be swap on just pointer for efficient

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <postgresql/libpq-fe.h>

using PGconnDeleter = std::function<void(PGconn*)>;
using PGresultClear = std::function<void(PGresult*)>;

using PGresultPTR = std::unique_ptr<PGresult, PGresultClear>;
using PGconnPTR = std::unique_ptr<PGconn, PGconnDeleter>;

class PostgresDB{
public:
    PostgresDB();

    PostgresDB(const PostgresDB&) = delete;
    PostgresDB& operator=(const PostgresDB&) = delete;

    PostgresDB(PostgresDB&&) noexcept;
    PostgresDB& operator=(PostgresDB&&) noexcept;

    bool connect(std::string&&);

    //need pre-connect on postgres-user for make a new db
    bool make_db(std::string&&);
    bool is_connect() const;

    template<typename Container>
    bool execute(std::string&&, Container&&) const;

    template<typename Container>
    std::vector<std::vector<std::string>> fetch(std::string&&, Container&&) const;

    void close();

private:
    PGconnPTR conn;

    template<typename Container>
    std::vector<const char*> params_transfrom(Container&&) const;
};

template<typename Container>
std::vector<const char*> PostgresDB::params_transfrom(Container&& container) const
{
    std::vector<const char*> n_params;
    for(const auto& obj : container){
        n_params.push_back(obj.c_str());
    }
    return n_params;
}

template<typename Container>
bool PostgresDB::execute(std::string&& query, Container&& container) const
{
    std::vector<const char*> n_params = params_transfrom(std::forward<Container>(container));

    PGresultPTR result(
        PQexecParams(conn.get(), query.c_str(), n_params.size(), 
        nullptr, n_params.data(), nullptr, nullptr, 0), 
        [](PGresult* res){ PQclear(res); }
    );
    
    return PQresultStatus(result.get()) == PGRES_COMMAND_OK;
}

template<typename Container>
std::vector<std::vector<std::string>> PostgresDB::fetch(std::string&& query, Container&& container) const
{
    std::vector<const char*> n_params = params_transfrom(std::forward<Container>(container));

    PGresultPTR result(
        PQexecParams(conn.get(), query.c_str(), n_params.size(),
        nullptr, n_params.data(), nullptr, nullptr, 0),
        [](PGresult* res){ PQclear(res); }
    );

    std::vector<std::vector<std::string>> table;

    int rows = PQntuples(result.get());
    int columns = PQnfields(result.get());

    for(int i = 0; i < rows; i++){
        std::vector<std::string> temp;
        for(int j = 0; j < columns; j++){
            temp.push_back(PQgetvalue(result.get(), i, j));
        }   
        table.emplace_back(std::move(temp));
    }

    return table;
}

#endif //_POSTGRES_DB_H_