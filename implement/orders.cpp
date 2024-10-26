#include "../includes/orders.hpp"
#include <cppconn/prepared_statement.h>
#include <nlohmann/json_fwd.hpp>
Orders::Orders(sql::Connection* conn):connection(conn){}
void Orders::addNewOrder(nlohmann::json& json, std::string code){
    std::string address  = json["address"];
   
    std::string desiredDate = json["date"];
    std::string entrance  = json["entrance"];
    std::string floor  = json["floor"];
    std::string performerId = json["userid"];
    std::string flat  = json["flat"];
    std::string phone  = json["phone"];
    std::string dateOfRecipte  = json["dateOfRecipte"];
    std::string timeOfRecipte  = json["timeOfRecipte"];
    std::string location  = json["location"];
    
    sql::PreparedStatement* pstmt = connection->prepareStatement(R"(INSERT INTO delivery_details 
            (address, entrance, floor, flat, phone, date_of_recipte, time_of_recipte, code, location, performer_id, desired_date)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?,?,?);)");
    pstmt->setString(1, address);
    pstmt->setString(2, entrance);
    pstmt->setString(3, floor);
    pstmt->setString(4, flat);
    pstmt->setString(5, phone);
    pstmt->setString(6, dateOfRecipte);
    pstmt->setString(7, timeOfRecipte);
    pstmt->setString(8, code);
    pstmt->setString(9, location);
    pstmt->setString(10, performerId);
    pstmt->setString(11, desiredDate);

    pstmt->execute();
}