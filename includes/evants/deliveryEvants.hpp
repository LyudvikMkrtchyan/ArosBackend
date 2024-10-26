#include "../evantSwitch.hpp"

using request = boost::beast::http::request<boost::beast::http::string_body>;
using response = boost::beast::http::response<boost::beast::http::string_body>; 

void addDelivery(const request& req, response& res , DataBase& db);

void evantSwitchInitalaizDelivery(EvantSwitch &evantsMap);