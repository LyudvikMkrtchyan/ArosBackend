#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class Delivery{
public:
    Delivery(sql::Connection* connection);
    void addDelivery(nlohmann::json& json);
 
private:
    sql::Connection* connection;
};