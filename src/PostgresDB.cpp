#include "PostgresDB.h"

PostgresDB::PostgresDB() = default;

bool PostgresDB::connect(std::string&& val)
{
    PGconn* temp_conn = PQconnectdb(val.c_str());

    if(!temp_conn)
        return 0;

    if(PQstatus(temp_conn) == CONNECTION_BAD){
        PQfinish(temp_conn);
        return 0;
    }

    conn = PGconnPTR(
        temp_conn, 
        [](PGconn* ptr){ PQfinish(ptr); }
    );

    return 1;
}

void PostgresDB::close()
{
    if(conn)
        conn.reset();
}

bool PostgresDB::is_connect() const
{
    return PQstatus(conn.get()) == CONNECTION_OK;
}

PostgresDB::PostgresDB(PostgresDB&& obj) noexcept : conn(std::move(obj.conn))
{}

PostgresDB& PostgresDB::operator=(PostgresDB&& obj) noexcept
{
    if(this == &obj)
        return *this;

    conn = std::move(obj.conn);
    return *this;
}

bool PostgresDB::make_db(std::string&& name)
{
    PGresultPTR result (
        PQexec(conn.get(), ("CREATE DATABASE " + name).c_str()),
        [](PGresult* res){ PQclear(res); }
    );

    if(PQresultStatus(result.get()) != PGRES_COMMAND_OK){
        return 0;
    }

    return 1;
}

PostgresDB::~PostgresDB(){
    this->close();
}