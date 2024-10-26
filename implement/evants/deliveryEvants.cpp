#include "../../includes/evants/deliveryEvants.hpp"

void addDelivery(const request &req, response &res, DataBase &db){
    nlohmann::json json = nlohmann::json::parse(req.body());
    db.addDelivery(json);
};



void evantSwitchInitalaizDelivery(EvantSwitch &evantsMap){
    evantsMap.addEvant("/addDelivery", addDelivery);
}