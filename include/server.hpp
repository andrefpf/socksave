#ifndef __SOCK_SERVER_HPP__ 
#define __SOCK_SERVER_HPP__

#include <iostream>
#include <list>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>


namespace socksave {

struct Connection {
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf buffer;
    
    Connection( boost::asio::io_service & io_service ) : socket( io_service ), buffer() { }
};

class Server {
    public:
        Server(int server_port);
        void run();

        void start_accepting();
        void start_reading(std::list<Connection>::iterator connection);

    private:
        void read_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error);
        void accept_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error);
    
    public:
        int port;

    private:
        boost::asio::io_service _io_service;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::acceptor _acceptor;
        std::list<Connection> _connections; 
};

}   // socksave

#endif