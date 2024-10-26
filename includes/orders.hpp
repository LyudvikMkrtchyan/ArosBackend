#pragma once
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include "nlohmann/json.hpp"
class Orders{
public:
    Orders(sql::Connection* conn);
    void addNewOrder(nlohmann::json& json, std::string code);
private:
    sql::Connection* connection;
};