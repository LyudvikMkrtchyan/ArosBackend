#include "../includes/carpets.hpp"
#include <cppconn/connection.h>
#include <cppconn/datatype.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include <iomanip>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <sstream>

Carpets::Carpets(sql::Connection* conn):connection(conn){}
nlohmann::json Carpets::getCarpets(){
    std::cout << "Carpets::getCarpets is runned" << std::endl;
    std::unique_ptr<sql::Statement> stmt(connection->createStatement());
    
    std::shared_ptr<sql::ResultSet> res(stmt->executeQuery(
        R"(SELECT address, phone_number, pickup_date, desired_date, status, code, id 
           FROM Carpets 
           ORDER BY desired_date ASC)"));
    
    return extractCarpets(res);
}
nlohmann::json Carpets::getWashedCarpets(){
    nlohmann::json answerJson = nlohmann::json::array();
    std::cout << "Carpets::getWashedCarpets is runned" << std::endl;
    std::unique_ptr<sql::Statement> stmt(connection->createStatement());
    
    std::shared_ptr<sql::ResultSet> res(stmt->executeQuery(
        R"(SELECT wash_date, phone_number, address, desired_date, surface,price, code 
           FROM Carpets Where status='clean'
           ORDER BY wash_date ASC)"));
    
    while(res->next()){
        nlohmann::json tmp;

        tmp["washedDate"] = res->getString("wash_date");
        tmp["phoneNumber"] = res->getString("phone_number");
        tmp["address"] = res->getString("address");
        tmp["desiredDate"] = res->getString("desired_date");  
        tmp["surface"] = res->getString("surface");
        tmp["price"] = res->getString("price");
        tmp["code"] = res->getString("code"); 
    
        answerJson.push_back(tmp);
    }

    return answerJson;
}
void Carpets::addCarpet(nlohmann::json& json){
   
    std::string pickupDate = time->getTodaysDate();
    std::string address = json["address"];
    std::string entrance = json["entrance"];
    std::string phoneNumber = json["phoneNumber"];
    std::string floor = json["floor"];
    std::string flat = json["flat"];
 
    std::string code = json["code"];
    

    std::string location = json["location"];
    std::string desiredDate = json["date"];

    
    if(json.contains("idDeliveryToWash")){

    }else{
        std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(INSERT INTO Carpets 
                                                (address, entrance, phone_number, pickup_date, floor, flat, code, location, desired_date) 
                                                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?) )"));
        pstmt->setString(1, address);
        pstmt->setString(2, entrance);
        pstmt->setString(3, phoneNumber);
        pstmt->setString(4, pickupDate);
        pstmt->setString(5, floor);
        pstmt->setString(6, flat);
        pstmt->setString(7, code);
        pstmt->setString(8, location);
        pstmt->setString(9, desiredDate);


        pstmt->execute();
    }

  
// id_delivery_to_washing = int  
// id_delivery_to_home    = int  
// wash_date              = date     
// delivery_date          = date 
// washer                 = int 
// surface                = double 
// price                  = double      
// status                 = enum(dirty, clean) default dirty
// expected_date          = date 
// code                   = int       
// desired_date           = date
// location               = enum(abovyan, other) 
}
void Carpets::setCarpetParametrFromWasher(nlohmann::json& json){
    std::string code = json["code"];
    int workerId = json["workerId"];
    double surface = json["surface"];
    int price = json["price"];
    price *= surface;

    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(UPDATE Carpets
                                                                        SET washer = ?, surface = ?, price = ?, status='washing'
                                                                        WHERE code = ?;)"));
    pstmt->setInt(1, workerId);
    pstmt->setDouble(2, surface);
    pstmt->setDouble(3, price);
    pstmt->setString(4, code);

    bool ok = pstmt->execute();
}
void Carpets::setCarpetStatusClean(std::string carpetCode){
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement("Update Carpets Set status='clean' where code=?;"));

    pstmt->setString(1, carpetCode);
    pstmt->execute();
}
void Carpets::setCarpetsParametrsForDelivery(nlohmann::json& json){
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(Update Carpets
                                                                                    set status='being_delivered',
                                                                                        delivery_date=?,
                                                                                        delivery_time=?
                                                                                    Where code=?)"));
    
    std::string deliveryDate = json["deliveryDate"];
    std::string deliveryTime = json["deliveryTime"];
    
    pstmt->setString(1, deliveryDate);
    pstmt->setString(2, deliveryTime);

    std::vector<std::string> codes = json["codes"].get<std::vector<std::string>>();

    for(auto code : codes){
        pstmt->setString(3, code);
        pstmt->execute();
    }
}
void Carpets::setCarpetWashDay(std::string carpetCode){
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement("Update Carpets Set wash_date=? where code=?;"));
    std::string dateToday = time->getTodaysDate();

    pstmt->setString(1, dateToday);
    pstmt->setString(2, carpetCode);
    pstmt->execute();
}

nlohmann::json Carpets::getCarpetInfo(int id){
    nlohmann::json answer;
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement("Select * From Carpets Where id=?;"));
    pstmt->setInt(1, id);

    sql::ResultSet* res = pstmt->executeQuery();

    if(res->next()){
         answer["id"] = res->getInt("id");
        answer["address"] = res->getString("address");
        answer["entrance"] = res->getString("entrance");
        answer["phone_number"] = res->getString("phone_number");
        answer["floor"] = res->getString("floor");
        answer["flat"] = res->getString("flat");
        answer["pickup_date"] = res->getString("pickup_date");
        answer["id_delivery_to_washing"] = res->getInt("id_delivery_to_washing");
        answer["id_delivery_to_home"] = res->getInt("id_delivery_to_home");
        answer["wash_date"] = res->getString("wash_date");
        answer["delivery_date"] = res->getString("delivery_date");
        answer["washer"] = res->getInt("washer");
        answer["surface"] = res->getDouble("surface");
        answer["price"] = res->getDouble("price");
        answer["status"] = res->getString("status");
        answer["code"] = res->getString("code");
        answer["desired_date"] = res->getString("desired_date");
        answer["location"] = res->getString("location");
    }
    std::cout << answer.dump(4) << std::endl;
    return answer;
}
nlohmann::json Carpets::getCarpetsForWash(int duringTIme){
    nlohmann::json answerJson = nlohmann::json::array();

    std::string dateToday = time->getTodaysDate();

    std::string highDate = time->addDaysToDate(dateToday, duringTIme);

    sql::PreparedStatement* pstmp = connection->prepareStatement("Select address, code, desired_date From Carpets where desired_date<=? and status='dirty'");
    pstmp->setString(1, highDate);
    sql::ResultSet* res = pstmp->executeQuery();

    while(res->next()){
        std::string desired_date = res->getString("desired_date");
        std::string washDate = Time().addDaysToDate(desired_date, -(duringTIme));
        std::string address = res->getString("address");
        std::string code = res->getString("code");

        nlohmann::json tmp;
        tmp["washDate"] = washDate;
        tmp["address"]      = address;
        tmp["code"]         = code;

        answerJson.push_back(tmp);
    }

    return answerJson;
    
}
nlohmann::json Carpets::getActualCarpetForWasher(int washeId){
    nlohmann::json answer;
    sql::PreparedStatement* pstmt = connection->prepareStatement("Select code, surface From Carpets Where status='washing' and washer=?;");
    pstmt->setInt(1, washeId);
    sql::ResultSet* res = pstmt->executeQuery();
    if(res->next()){
        answer["code"] = res->getString("code");
        answer["surface"] = res->getDouble("surface");
    }
    return answer;
    
}
std::string Carpets::getCarpetLocation(std::string code){
    std::string location;
    sql::PreparedStatement* pstmt = connection->prepareStatement("Select location From Carpets Where code=?;");
    pstmt->setString(1, code);
    sql::ResultSet* res = pstmt->executeQuery();

    if(res->next()){
        location = res->getString("location");
    }
    return location;
}
nlohmann::json Carpets::getCarpetsReadyForDelivery(std::string date){
    nlohmann::json answerJson = nlohmann::json::array();
    std::cout << "Carpets::getWashedCarpets is runned" << std::endl;
    std::unique_ptr<sql::Statement> stmt(connection->createStatement());
    
    std::shared_ptr<sql::ResultSet> res(stmt->executeQuery(
        R"(SELECT wash_date, phone_number, address, desired_date, surface,price, code 
           FROM Carpets Where status='being_delivered'
           ORDER BY wash_date ASC)"));
    
    while(res->next()){
        nlohmann::json tmp;

        tmp["washedDate"] = res->getString("wash_date");
        tmp["phoneNumber"] = res->getString("phone_number");
        tmp["address"] = res->getString("address");
        tmp["desiredDate"] = res->getString("desired_date");  
        tmp["surface"] = res->getString("surface");
        tmp["price"] = res->getString("price");
        tmp["code"] = res->getString("code"); 
    
        answerJson.push_back(tmp);
    }

    return answerJson; 
}
nlohmann::json Carpets::searchWithPhoneNumber(std::string phoneNumber) {
    
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(
    Select address, phone_number, pickup_date, desired_date, , status, code 
    From carpets Where phone_number=?)"));
    pstmt->setString(1, phoneNumber);

    
    std::shared_ptr<sql::ResultSet> res(pstmt->executeQuery());
    return extractCarpets(res);
}
nlohmann::json Carpets::searchWithAddress(std::string address) {
    
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(
    Select address, phone_number, pickup_date, expected_date, surface, price, status, code 
    From carpets Where address=?)"));
    pstmt->setString(1, address);

    
  
    std::shared_ptr<sql::ResultSet> res(pstmt->executeQuery());
    return extractCarpets(res);
}
nlohmann::json Carpets::searchWithCode(std::string code) {
    
     std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(
    Select address, phone_number, pickup_date, expected_date, surface, price, status, code 
    From carpets Where code=?)"));
    pstmt->setString(1, code);

    
    std::shared_ptr<sql::ResultSet> res(pstmt->executeQuery());
    return extractCarpets(res);
}

nlohmann::json Carpets::extractCarpets(std::shared_ptr<sql::ResultSet> res){
    nlohmann::json answerJson = nlohmann::json::array();

    while(res->next()) {
        nlohmann::json tmp;

        tmp["address"] = res->getString("address");
        tmp["phoneNumber"] = res->getString("phone_number");
        tmp["pickupDate"] = res->getString("pickup_date");
        tmp["desiredDate"] = res->getString("desired_date");  
        tmp["status"] = res->getString("status");
        tmp["code"] = res->getString("code"); 
        tmp["id"] = res->getString("id"); 

        
        answerJson.push_back(tmp); 
        
    }

        std::cout << answerJson.dump(4) << std::endl;
    return answerJson;
}
nlohmann::json Carpets::getHeavyBurden(std::string date){
    std::string endDate = time->addDaysToDate(date, 15);

    nlohmann::json answerJson = nlohmann::json::array();
    std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(R"(SELECT expected_date, COUNT(*) AS product_count
                                                FROM Carpets
                                                WHERE expected_date BETWEEN ? AND ?
                                                GROUP BY expected_date
                                                ORDER BY expected_date;  
                                                )"));
    pstmt->setString(1, date);
    pstmt->setString(2, endDate);

    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    while(res->next()){
        nlohmann::json tmp;
        
        tmp["date"] = res->getString("expected_date");
        tmp["count"] = res->getInt("product_count");

        answerJson.push_back(tmp);
    }
    std::cout << answerJson.dump(4) << std::endl;
    return answerJson;


 
}
 
