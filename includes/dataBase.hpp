#pragma once
#include "carpets.hpp"
#include "time.h"
#include "workers.hpp"
#include "options.hpp"
#include "finances.hpp"
#include "orders.hpp"
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <ctime>
class DataBase:public Workers, public Carpets,public Orders, public Options, public Finances{
public:
    DataBase(sql::Connection* );
private:
    sql::Connection* connection;
public:
};
sql::Connection* connect(std::string, std::string, std::string);