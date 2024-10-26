#include "../includes/dataBase.hpp"
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include <mysql_connection.h>
#include <mysql_driver.h>
template <typename Tp>
using Uptr = std::unique_ptr<Tp>;

DataBase::DataBase(sql::Connection* conn):Workers(conn), 
                                          Carpets(conn), 
                                          Orders(conn), 
                                          Options(conn),
                                          Finances(conn),
                                          connection(conn){};

sql::Connection* connect(std::string login, std::string password, std::string dataBaseNaem){
    Uptr<sql::mysql::MySQL_Driver> driver(sql::mysql::get_driver_instance());
    sql::Connection* connection;

    connection = driver->connect("tcp://127.0.0.1:3306", login, password);
    connection->setSchema(dataBaseNaem);
    return connection;
}


    
    


