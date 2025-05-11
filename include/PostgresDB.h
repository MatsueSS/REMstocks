#ifndef _POSTGRES_DB_H_
#define _POSTGRES_DB_H_

//In future std::function can will be swap on just pointer, but with conditions

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

    bool connect(std::string);

    bool make_db();
    bool is_connect() const;

    template<typename InType>
    void execute(std::string&&, std::vector<InType>&&) const;

    template<typename Intype, typename OutType>
    std::vector<std::vector<OutType>> fetch(std::string&&, std::vector<Intype>&&);

    void close();

private:
    PGconnPTR conn;

};

#endif //_POSTGRES_DB_H_