#pragma once
#include "time.hpp"
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class Carpets{
public:
    Carpets(sql::Connection* connection);
public:
    void addCarpet(nlohmann::json& json);
    void setCarpetParametrFromWasher(nlohmann::json& json);
    void setCarpetStatusClean(std::string carpetCode);
    void setCarpetWashDay(std::string carpetCode);
    void setCarpetsParametrsForDelivery(nlohmann::json& json);

    
    nlohmann::json getCarpets();
    nlohmann::json getWashedCarpets();
    nlohmann::json getCarpetInfo(int id);
    nlohmann::json getCarpetsForWash(int duringTime);
    nlohmann::json getCarpetsReadyForDelivery(std::string date);
    nlohmann::json getHeavyBurden(std::string date);
    nlohmann::json getActualCarpetForWasher(int washerId);
    std::string getCarpetLocation(std::string code);



    nlohmann::json searchWithPhoneNumber(std::string phoneNumber);
    nlohmann::json searchWithAddress(std::string address);
    nlohmann::json searchWithCode(std::string code);

private:
    nlohmann::json extractCarpets(std::shared_ptr<sql::ResultSet> );
    Time* time;
private:
    sql::Connection* connection;
};