#include <server.hpp>


socksave::LogServer::LogServer(int server_port, 
                               int file_size, 
                               boost::filesystem::path dir, 
                               std::string prefix): 
                               
                               _endpoint(boost::asio::ip::tcp::v4(), server_port),
                               _acceptor(_io_service, _endpoint),
                               _port(server_port),
                               _file_size(file_size),
                               _dir(dir),
                               _prefix(prefix)
{
    _total_connections = 0;
} 

void socksave::LogServer::run() {
    start_accepting();
    _io_service.run();
}

void socksave::LogServer::start_accepting() {
    std::string subdir;

    subdir  = "connection";
    subdir += "_" + get_timestamp();
    subdir += "_" + std::to_string(_total_connections);

    auto connection = _connections.emplace(_connections.begin(), _io_service, _file_size, _dir/subdir, _prefix);
    auto handler = boost::bind(&socksave::LogServer::accept_handler, this, connection, boost::asio::placeholders::error);
    _acceptor.async_accept(connection->socket, handler);
}

void socksave::LogServer::start_reading(std::list<Connection>::iterator connection) {
    auto handler = boost::bind(&socksave::LogServer::read_handler, this, connection, boost::asio::placeholders::error);
    boost::asio::async_read_until(connection->socket, connection->buffer, "\0", handler);
}


void socksave::LogServer::accept_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error) {
    if (error) {
        std::cerr << "LogServer Error: " << error.message() << std::endl;
        _connections.erase(connection);
        return;
    } 

    _total_connections++;

    // connection info
    std::string ip = connection->socket.remote_endpoint().address().to_string();
    int port = connection->socket.remote_endpoint().port();

    std::cout << "Conection accepted" << std::endl;
    std::cout << "IP: " << ip << "\t PORT: " << port << std::endl; 
    std::cout << std::endl;

    start_reading(connection);
    start_accepting();
} 

void socksave::LogServer::read_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error) {
    if (error) {
        std::cerr << "LogServer Error: " << error.message() << std::endl;
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

    connection->datastore.write(msg);

    start_reading(connection);
} 