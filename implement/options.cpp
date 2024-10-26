#include "../includes/options.hpp"
#include <cassert>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <nlohmann/json_fwd.hpp>
#include <string>

Options::Options(sql::Connection* conn):connection(conn){};

nlohmann::json Options::getOptions(){
    nlohmann::json answer;
    sql::Statement* stmt = connection->createStatement();
    sql::ResultSet* res = stmt->executeQuery("Select * From Options");

    while(res->next()){
        std::string key = res->getString("option_name");
        int value = res->getInt("option_value");
        answer[key] = value;
    }

    std::cout << answer.dump(4) << std::endl;
    return answer;
}
int Options::getDuringTime(){
    sql::Statement* stmt = connection->createStatement();
    sql::ResultSet* res = stmt->executeQuery("Select option_value From Options where option_name='during_time';");
    res->next();
    int duringTime = res->getInt("option_value");
    return duringTime;

}
int Options::getPrice(std::string location){
    int price = 0;
    std::string priceType = convertLocationPriceType(location);
    sql::PreparedStatement* pstmt = connection->prepareStatement("Select option_value From Options Where option_name=?");
    pstmt->setString(1, priceType);

    sql::ResultSet* res = pstmt->executeQuery();
    if(res->next()){
        price = res->getInt("option_value");
    }else{
        assert(false && "Error priceType in function GetPrice");
    }
    return price;
}
void Options::updateOptions(nlohmann::json& json){

    for(auto it = json.begin(); it != json.end(); ++it){
    sql::PreparedStatement* pstmp = connection->prepareStatement(R"(UPDATE Options
                                                                        SET option_value = ?
                                                                        WHERE option_name=?;)");
    
        std::string optionName = it.key();
        int optionValue = it.value();
        pstmp->setInt(1,optionValue);
        pstmp->setString(2,optionName);
        pstmp->execute();
    }
}
std::string Options::convertLocationPriceType(std::string location){
    std::string priceType;
    
    if(location == "abovyan"){
        priceType = "price_nearby";
    }else if(location == "other"){
        priceType = "price_far_away";
    }

    return priceType;
}
