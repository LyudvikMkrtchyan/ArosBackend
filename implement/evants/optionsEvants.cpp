#include "../../includes/evants/optionsEvants.hpp"
#include <nlohmann/json_fwd.hpp>

void getOptions(const request& req, response& res , DataBase& db){
    std::cout << "getOptions is runned" << std::endl;
    
    nlohmann::json answerJson;

    answerJson = db.getOptions();
    
    if(!answerJson.empty()){
        std::cout << answerJson.dump(4) << std::endl;
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
}
void updateOptions(const request& req, response& res , DataBase& db){
    std::cout << "updateOptions is runned" << std::endl;

    nlohmann::json json = nlohmann::json::parse(req.body());
    db.updateOptions(json);

}
void evantSwitchInitalaizOptions(EvantSwitch &evantsMap){
    evantsMap.addEvant("/getOptions", getOptions);
    evantsMap.addEvant("/updateOptions", updateOptions);
}