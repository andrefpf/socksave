#ifndef __LOG_SERVER_HPP__ 
#define __LOG_SERVER_HPP__

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <list>
#include <datastore.hpp>
#include <utils.hpp>
#include <config.hpp>

namespace socksave {

struct Connection {
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf buffer;
    DataStore datastore;

    Connection(boost::asio::io_service & io_service, 
               int max_size, 
               boost::filesystem::path path, 
               std::string prefix): 
               
               socket( io_service ), buffer(), datastore(max_size, path, prefix) { }
};

class LogServer {
    public:
        LogServer(int server_port, int file_size, int timeout, boost::filesystem::path path, std::string prefix);
        LogServer(Config * config);
        
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
        int _timeout;
        int _total_connections;

        int _file_size;
        boost::filesystem::path _path;
        std::string _prefix;
};

}   // socksave

#endif