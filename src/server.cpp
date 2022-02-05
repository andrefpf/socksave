#include <server.hpp>

socksave::LogServer::LogServer(int server_port, 
                               int timeout,
                               int file_size, 
                               boost::filesystem::path path, 
                               std::string prefix): 
                               
                               _endpoint(boost::asio::ip::tcp::v4(), server_port),
                               _acceptor(_io_service, _endpoint),
                               _port(server_port),
                               _timeout(timeout),
                               _file_size(file_size),
                               _path(path),
                               _prefix(prefix)
{
    _total_connections = 0;
} 

socksave::LogServer::LogServer(Config * config) : LogServer(config->port, 
                                                            config->timeout,
                                                            config->max_size, 
                                                            config->path, 
                                                            config->prefix) 
{}

void socksave::LogServer::run() {
    start_accepting();
    _io_service.run();
}

void socksave::LogServer::start_accepting() {
    std::string subdir;

    subdir  = "connection";
    subdir += "_" + get_timestamp();
    subdir += "_" + std::to_string(_total_connections);

    auto connection = _connections.emplace(_connections.begin(), _io_service, _timeout, _file_size, _path/subdir, _prefix);
    auto handler = boost::bind(&socksave::LogServer::accept_handler, this, connection, boost::asio::placeholders::error);
    _acceptor.async_accept(connection->socket, handler);
}

void socksave::LogServer::start_reading(std::list<Connection>::iterator connection) {
    auto handler = boost::bind(&socksave::LogServer::read_handler, this, connection, boost::asio::placeholders::error);
    boost::asio::async_read_until(connection->socket, connection->buffer, "\0", handler);
}

void socksave::LogServer::start_waiting(std::list<Connection>::iterator connection) {
    auto handler = boost::bind(&socksave::LogServer::wait_handler, this, connection, boost::asio::placeholders::error);
    connection->timer.expires_from_now(boost::posix_time::seconds(_timeout));
    connection->timer.async_wait(handler);
}

void socksave::LogServer::accept_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error) {
    switch (error.value()) {
        case 0: // not a error
            break;
        case boost::asio::error::operation_aborted:
            return;
        default:
            std::cerr << "LogServer::accept_handler Error: " << error.message() << std::endl;
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

    start_waiting(connection);
    start_reading(connection);
    start_accepting();
} 

void socksave::LogServer::read_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error) {
    switch (error.value()) {
        case 0: // not a error
            break;
        case boost::asio::error::operation_aborted:
            return;
        default:
            std::cerr << "LogServer::read_handler Error: " << error.message() << std::endl;
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
    start_waiting(connection);
    start_reading(connection);
} 

void socksave::LogServer::wait_handler(std::list<Connection>::iterator connection, boost::system::error_code const & error) {

    switch (error.value()) {
        case 0: // not a error
            break;
        case boost::asio::error::operation_aborted:
            return;
        default:
            std::cerr << "LogServer::wait_handler Error: " << error.message() << std::endl;
            _connections.erase(connection);
            return;
    }

    // connection info
    std::string ip = connection->socket.remote_endpoint().address().to_string();
    int port = connection->socket.remote_endpoint().port();

    std::cout << "Connection " << ip << "/" << port << " timed out!" << std::endl;
    connection->socket.close();       
}