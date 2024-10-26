#include "../evantSwitch.hpp"
#include "../dataBase.hpp"
#include <boost/beast/http/status.hpp>
#include <nlohmann/json_fwd.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http/verb.hpp>
using request = boost::beast::http::request<boost::beast::http::string_body>;
using response = boost::beast::http::response<boost::beast::http::string_body>; 

void addNewProduct(const request& req, response& res , DataBase& db);
void searchWithPhoneNumber(const request& req, response& res , DataBase& db);
void searchWithAddress(const request& req, response& res , DataBase& db);
void searchWithCode(const request& req, response& res , DataBase& db);
void getHeavyBurden(const request& req, response& res , DataBase& db);


void evantSwitchInitalaizProductManipulation(EvantSwitch& evantsMap);