#include "PostgresDB.h"

bool PostgresDB::connect(std::string val)
{
    PGconn* temp_conn = PQconnectdb(val.c_str());

    if(!temp_conn)
        return 0;

    if(PQstatus(temp_conn) == CONNECTION_BAD){
        PQfinish(temp_conn);
        return 0;
    }

    conn = PGconnPTR(temp_conn, [](PGconn* ptr){ PQfinish(ptr); });

    return 1;
}