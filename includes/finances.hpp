#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include "nlohmann/json.hpp"
#include "time.hpp"
class Finances{
public:
    Finances(sql::Connection* conn);
    void setTransactionWashFinance(int washerId, int amount,std::string code);
private:
    sql::Connection* connection;
    Time* time;
};