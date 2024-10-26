#include "../../includes/evants/ordersEvants.hpp"
#include <nlohmann/json_fwd.hpp>

void addOrder(const request& req, response& res , DataBase& db){
    nlohmann::json json = nlohmann::json::parse(req.body());
    std::cout << json.dump(4) << std::endl;
    int carpetsCount = json["count"];
    std::string rowCode = json["code"];
    for(int i = 1; i <= carpetsCount; ++i){
        std::string code = rowCode + '/' + std::to_string(i);
        db.addNewOrder(json, code);
    }
}


void evantSwitchInitalaizOrders(EvantSwitch &evantsMap){
   evantsMap.addEvant("/addOrder", addOrder);
}