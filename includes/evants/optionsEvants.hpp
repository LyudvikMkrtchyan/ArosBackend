#include "../evantSwitch.hpp"

using request = boost::beast::http::request<boost::beast::http::string_body>;
using response = boost::beast::http::response<boost::beast::http::string_body>; 

void getOptions(const request& req, response& res , DataBase& db);
void updateOptions(const request& req, response& res , DataBase& db);

void evantSwitchInitalaizOptions(EvantSwitch &evantsMap);