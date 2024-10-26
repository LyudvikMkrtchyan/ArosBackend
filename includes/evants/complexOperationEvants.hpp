#include "../evantSwitch.hpp"
#include "../dataBase.hpp"
#include "nlohmann/json.hpp"
#include <boost/beast/http/status.hpp>
#include <iostream>
#include <iterator>
#include <nlohmann/json_fwd.hpp>
#include <string_view>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http/verb.hpp>

using request = boost::beast::http::request<boost::beast::http::string_body>;
using response = boost::beast::http::response<boost::beast::http::string_body>; 

void theCarpetIsWashed(const request& req, response& res , DataBase& db);
void evantSwitchInitalaizComplexOperations(EvantSwitch& evantsMap);