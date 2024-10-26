#include "../../includes/evants/complexOperationEvants.hpp"
#include <nlohmann/json_fwd.hpp>

void theCarpetIsWashed(const request &req, response &res, DataBase &db){
    nlohmann::json json = nlohmann::json::parse(req.body());
    if(json["code"] != ""){
        std::cout << json.dump(4) << std::endl;
        int washerId = json["washerId"];
        double surface = json["surface"];
        std::string code = json["code"];
        int salary = db.getWorkerSalary(washerId);
        int amount = salary * surface;
    
        db.setTransactionWashFinance(washerId,amount,code);
        db.setCarpetStatusClean(code);
        db.setCarpetWashDay(code);
    }
}

void evantSwitchInitalaizComplexOperations(EvantSwitch& evantsMap){
    evantsMap.addEvant("/theCarpetIsWashed", theCarpetIsWashed);
}

