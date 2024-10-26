#include "../../includes/evants/carpetsManipulation.hpp"
#include <boost/beast/http/status.hpp>
#include <nlohmann/json_fwd.hpp>

void addCarpet(const request& req, response& res , DataBase& db){
    std::cout << "add New Product is runed" << std::endl;
    nlohmann::json json = json.parse(req.body());

    db.addCarpet(json); 
}
void prepareCarpetForDelivery(const request& req, response& res , DataBase& db){
    std::cout << "prepareCarpetForDelivery is runned" << std::endl;
    nlohmann::json json = nlohmann::json::parse(req.body());
    db.setCarpetsParametrsForDelivery(json);
}
void getCarpets(const request& req, response& res , DataBase& db){
    std::cout << "get Carpetsis runed" << std::endl;
    nlohmann::json json = json.parse(req.body());
    nlohmann::json answerJson;
    answerJson =  db.getCarpets();
    
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
}
void getWashedCarpets(const request& req, response& res , DataBase& db){
    std::cout << "get Washed Carpetsis runed" << std::endl;
    nlohmann::json json = json.parse(req.body());
    nlohmann::json answerJson;
    answerJson =  db.getWashedCarpets();
    
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
}
void getActualCarpetForWasher(const request& req, response& res , DataBase& db){
    std::cout << "get Actual Carpet For Washer is runed" << std::endl;

    nlohmann::json json = nlohmann::json::parse(req.body());
    nlohmann::json answer;
    
    int washerId = json["washerId"];

    answer = db.getActualCarpetForWasher(washerId);
    if(!answer.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answer.dump();

}
void getCarpetInfo(const request& req, response& res , DataBase& db){
    nlohmann::json answerJson;
    int carpetId = nlohmann::json::parse(req.body())["id"];

    answerJson = db.getCarpetInfo(carpetId); 
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    
}
void getCarpetsForWash(const request& req, response& res , DataBase& db){
    nlohmann::json answerJson = nlohmann::json::array();
    int duringTIme = db.getDuringTime();

    answerJson = db.getCarpetsForWash(duringTIme);

    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    std::cout << answerJson.dump(4) << std::endl;
}
void getReadyForDeliveryCarpets(const request& req, response& res , DataBase& db){
    nlohmann::json answerJson = nlohmann::json::array();
    std::string date = nlohmann::json::parse(req.body())["date"];

    answerJson = db.getCarpetsReadyForDelivery(date);

       if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();

}
void searchWithPhoneNumber(const request& req, response& res , DataBase& db){
    std::cout << "switch with number is runed" << std::endl;
    nlohmann::json json = json.parse(req.body());
    std::string phoneNumber = json["phoneNumber"];
    nlohmann::json answerJson;
    answerJson =  db.searchWithPhoneNumber(phoneNumber);
    
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    
}
void searchWithAddress(const request& req, response& res , DataBase& db){
     std::cout << "search with addres is runed" << std::endl;
    nlohmann::json json = json.parse(req.body());
    std::string address = json["address"];
    nlohmann::json answerJson;
    answerJson =  db.searchWithAddress(address);
    
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    
}
void searchWithCode(const request& req, response& res , DataBase& db){
     std::cout << "switch with code is runed" << std::endl;
    nlohmann::json json = json.parse(req.body());
    std::string code = json["code"];
    nlohmann::json answerJson;
    answerJson =  db.searchWithCode(code);
    
    if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    
}
void getHeavyBurden(const request& req, response& res , DataBase& db){
     std::cout << "geatHeavyBurden  is runed" << std::endl;
    nlohmann::json json = json.parse(req.body());
    std::string date = json["date"];  
    
     nlohmann::json answerJson;
    answerJson =  db.getHeavyBurden(date);

     if(!answerJson.empty()){
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();

}
void setCarpetParametrFromWasher(const request& req, response& res , DataBase& db){
    nlohmann::json json = nlohmann::json::parse(req.body());
    std::string code = json["code"];
    std::string location = db.getCarpetLocation(code);
    int price = db.getPrice(location);
    
    json["price"] = price;
    
    db.setCarpetParametrFromWasher(json);
    



}
void evantSwitchInitalaizProductManipulation(EvantSwitch& evantsMap){
    evantsMap.addEvant("/addCarpet", addCarpet);
    evantsMap.addEvant("/getCarpets", getCarpets);
    evantsMap.addEvant("/getWashedCarpets", getWashedCarpets);
    evantsMap.addEvant("/getActualCarpetForWasher", getActualCarpetForWasher);
    evantsMap.addEvant("/searchWithPhoneNumber", searchWithPhoneNumber);
    evantsMap.addEvant("/searchWithAddress", searchWithAddress);
    evantsMap.addEvant("/searchWithCode", searchWithCode);
    evantsMap.addEvant("/getHeavyBurden", getHeavyBurden);
    evantsMap.addEvant("/getCarpetInfo", getCarpetInfo);
    evantsMap.addEvant("/getCarpetsForWash", getCarpetsForWash);
    evantsMap.addEvant("/setCarpetParametrFromWasher", setCarpetParametrFromWasher);
    evantsMap.addEvant("/prepareCarpetForDelivery", prepareCarpetForDelivery);
    evantsMap.addEvant("/getReadyForDeliveryCarpets", getReadyForDeliveryCarpets);




}