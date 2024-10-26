#include "../includes/delivery.hpp"
#include <cppconn/connection.h>

Delivery::Delivery(sql::Connection* conn):connection(conn){};

void Delivery::addDelivery(nlohmann::json& json){
    std::cout << "Delivery::addDelivery is runnes" << std::endl;
    std::vector<std::string> codes = json["codes"].get<std::vector<std::string>>();
    std::string date = json["deliveryDate"];
    std::string time = json["deliveryTime"];
    for(auto it : codes){
        std::cout << "code  : "  << it << std::endl;
        std::cout << "date  : "  << date << std::endl;
        std::cout << "time  : "  << time << std::endl;
        std::cout << std::endl;
    }
}