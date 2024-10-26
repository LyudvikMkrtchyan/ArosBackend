#include "../includes/dataBase.hpp"
#include "../includes/network.hpp"
#include "../includes/helperFunctions.hpp"
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <thread>

EvantSwitch evantSwitch;

int main(){
    evantSwitchInitalaiz(evantSwitch);
    sql::Connection* conn = connect("atlass", "123456", "validation");
   
    boost::asio::io_context context;
    boost::asio::ip::tcp::acceptor acceptor(context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 9091));
    DataBase db(conn);
    while(true){
        boost::asio::ip::tcp::socket socket(context);
        acceptor.accept(socket);
        std::thread(&session,std::move(socket), std::ref(db)).detach();
    }
}