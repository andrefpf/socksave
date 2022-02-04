#include <server.hpp>


socksave::Server::Server(int server_port): port(server_port),
                                                   _endpoint(boost::asio::ip::tcp::v4(), server_port),
                                                   _acceptor(_io_service, _endpoint)
{} 

void socksave::Server::run() {
    start_accepting();
    _io_service.run();
}

void socksave::Server::start_accepting() {
    auto connection = _connections.emplace(_connections.begin(), _io_service);
    auto handler = boost::bind(&socksave::Server::accept_handler, this, connection, boost::asio::placeholders::error);
    _acceptor.async_accept(connection->socket, handler);
}

void socksave::Server::start_reading(std::list<Connection>::iterator connection) {
    auto handler = boost::bind(&socksave::Server::read_handler, this, connection, boost::asio::placeholders::error);
    boost::asio::async_read_until(connection->socket, connection->buffer, "\0", handler);
}


void socksave::Server::accept_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error) {
    if (error) {
        std::cerr << "Server Error: " << error.message() << std::endl;
        _connections.erase(connection);
        return;
    }

    // connection info
    std::string ip = connection->socket.remote_endpoint().address().to_string();
    int port = connection->socket.remote_endpoint().port();

    std::cout << "Conection accepted" << std::endl;
    std::cout << "IP: " << ip << "\t PORT: " << port << std::endl; 
    std::cout << std::endl;

    start_reading(connection);
    start_accepting();
} 

void socksave::Server::read_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error) {
    if (error) {
        std::cerr << "Server Error: " << error.message() << std::endl;
        _connections.erase(connection);
        return;
    }

    // connection info
    std::string ip = connection->socket.remote_endpoint().address().to_string();
    int port = connection->socket.remote_endpoint().port();

    // Get data correctly from the buffer
    int size  = connection->buffer.size();
    auto begin = boost::asio::buffers_begin(connection->buffer.data());
    std::string msg(begin, begin + size);
    connection->buffer.consume(size);
    
    std::cout << ip << "/" << port << ": " << msg << std::endl;
    std::cout << std::endl;

    start_reading(connection);
} 