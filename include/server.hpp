#ifndef __SOCK_SERVER_HPP__ 
#define __SOCK_SERVER_HPP__

#include <iostream>
#include <list>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include <datastore.hpp>
#include <utils.hpp>

namespace socksave {

struct Connection {
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf buffer;
    DataStore datastore;

    Connection(boost::asio::io_service & io_service, 
               int max_size, 
               boost::filesystem::path dir, 
               std::string prefix): 
               
               socket( io_service ), buffer(), datastore(max_size, dir, prefix) { }
};

class LogServer {
    public:
        LogServer(int server_port, int file_size, boost::filesystem::path dir, std::string prefix);
        
        void run();
        void start_accepting();
        void start_reading(std::list<Connection>::iterator connection);

    private:
        void read_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error);
        void accept_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error);

    private:
        boost::asio::io_service _io_service;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::acceptor _acceptor;
        std::list<Connection> _connections; 
        int _port;
        int _total_connections;

        int _file_size;
        boost::filesystem::path _dir;
        std::string _prefix;
};

}   // socksave

#endif