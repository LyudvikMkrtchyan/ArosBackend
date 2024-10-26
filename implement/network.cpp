#include "../includes/network.hpp"
#include "../includes/evantSwitch.hpp"

#include <boost/beast/http/status.hpp>
#include <iostream>

#include <nlohmann/json_fwd.hpp>

extern EvantSwitch evantSwitch;

namespace beast = boost::beast;             // from <boost/beast.hpp>
namespace http = beast::http;               // from <boost/beast/http.hpp>
namespace net = boost::asio;                // from <boost/asio.hpp>
using tcp = net::ip::tcp; 
void session(boost::asio::ip::tcp::socket socket, DataBase& db){
    boost::beast::flat_buffer buffer;

    boost::beast::http::request<boost::beast::http::string_body> req;
    boost::beast::http::read(socket, buffer, req);
           std::cout << "session" << std::endl;
    boost::beast::http::response<boost::beast::http::string_body> res;
     if (req.method() == boost::beast::http::verb::options) {

        res.result(boost::beast::http::status::no_content);
        res.set(boost::beast::http::field::access_control_allow_origin, "*"); // или укажите конкретные источники
        res.set(boost::beast::http::field::access_control_allow_methods, "POST, GET, OPTIONS");
        res.set(boost::beast::http::field::access_control_allow_headers, "Content-Type");
        
    }else{
       res.set(boost::beast::http::field::access_control_allow_origin, "*");
       res.set(boost::beast::http::field::access_control_allow_methods, "POST, GET, OPTIONS");
       res.set(boost::beast::http::field::access_control_allow_headers, "Content-Type");
       FunctionPtr  handler = evantSwitch.getEvantHendler(req);
       std::cout << req.target() << std::endl; 
       handler(req,res,db);
    }
     http::write(socket, res);

}
