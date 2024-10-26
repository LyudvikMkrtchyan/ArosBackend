#include "../../includes/evants/workerEvants.hpp"
void login(const request& req, response& res , DataBase& db){
    std::cout << "login is runed" << std::endl;
    std::cout << "req method = " << req.method() << std::endl; 
    std::cout << req.body() << std::endl;
    nlohmann::json json = json.parse(req.body());
    nlohmann::json answerJson;
    std::string login = json["login"].get<std::string>();
    std::string password = json["password"].get<std::string>();
    std::string role = db.getRole(login, password).first;
    int userId = db.getRole(login, password).second;
    std::cout << "role = " << role << std::endl;
    std::cout << "id = " << userId << std::endl;

    if(!role.empty()){
        answerJson["role"] = role;
        answerJson["userId"] = userId;
        
        res.result(boost::beast::http::status::ok);
        res.set(boost::beast::http::field::content_type, "application/json");
        res.body() = answerJson.dump();
    }else{

        answerJson["error"] = "Invalid login or password";    
        res.result(boost::beast::http::status::unauthorized);
        res.set(boost::beast::http::field::content_type, "application/json");
        res.body() = answerJson.dump();
    }
}
void addWorker(const request& req, response& res , DataBase& db){
     std::cout << "add Worker is runed" << std::endl;
    nlohmann::json json = json.parse(req.body());
    db.addWorker(json);

}
void updateWorker(const request& req, response& res , DataBase& db){
    std::cout << "updateWorker for change" << std::endl;
    nlohmann::json json =  json.parse(req.body());
    db.updateWorker(json); 
}
void getAllWorkers(const request& req, response& res , DataBase& db){
     std::cout << "get all user is runed" << std::endl;
    nlohmann::json answerJson;

    answerJson = db.getAllWorker();
    
    if(!answerJson.empty()){
        std::cout << answerJson.dump(4) << std::endl;
        res.result(boost::beast::http::status::ok);
    }else{
        res.result(boost::beast::http::status::unauthorized);
    }
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = answerJson.dump();
    

}
void getUserForChange(const request& req, response& res , DataBase& db){
     std::cout << "get  user for change" << std::endl;
    nlohmann::json json =  json.parse(req.body()); 
    nlohmann::json answerJson;
    int workerId = json["id"];
     answerJson = db.getUserForChange(workerId);
    
    if(!answerJson.empty()){
         std::cout << answerJson.dump(4) << std::endl;
         res.result(boost::beast::http::status::ok);
     }else{
         res.result(boost::beast::http::status::unauthorized);
     }
     res.set(boost::beast::http::field::content_type, "application/json");
     res.body() = answerJson.dump();
    

}



void evantSwitchInitalaizWorkers(EvantSwitch &evantsMap){
    evantsMap.addEvant("/login", login);
    evantsMap.addEvant("/addWorker", addWorker);
    evantsMap.addEvant("/updateWorker", updateWorker);
    evantsMap.addEvant("/getAllWorkers", getAllWorkers);
    evantsMap.addEvant("/getUserForChange", getUserForChange);
}
