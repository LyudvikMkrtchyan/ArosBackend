#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include "nlohmann/json.hpp"

class Workers{
public:
    Workers(sql::Connection* connection);
public:
     std::pair<std::string, int> getRole(std::string, std::string);
     int getWorkerSalary(int workerId);
     void addWorker(nlohmann::json& json);
     nlohmann::json getAllWorker();
     nlohmann::json getUserForChange(int workerId);
     void updateWorker(nlohmann::json& json);
private:
    sql::Connection* connection;
};