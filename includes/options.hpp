#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include "nlohmann/json.hpp"
class Options{
public:
    Options(sql::Connection* conn);
    int getDuringTime();
    int getPrice(std::string code);
    nlohmann::json getOptions();
    void updateOptions(nlohmann::json& json);
public:
    std::string convertLocationPriceType(std::string location);
private:
    sql::Connection* connection;
};