#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem/fstream.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

static const int PORT = 1234;

void test_server() {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT);
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
    boost::asio::ip::tcp::socket socket(io_service);

    acceptor.accept(socket);

    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    std::string msg = boost::asio::buffer_cast<const char*>(buf.data());
    std::cout << msg << std::endl;
}   

void test_file_1() {
    boost::filesystem::ofstream file("teste.txt");

    std::string input;
    std::cin >> input;
    while (input != "no") {
        file << input << std::endl;
        std::cin >> input;
    }

    file << "Hello World!" << std::endl;
}

void test_file_2() {
    boost::filesystem::path path("output/");
    
    path /= "teste.txt";
    
    boost::filesystem::ofstream file(path);

    std::string msg = "ESSA É UMA MENSAGEM MEIO GRANDE QUE EU ESTOU COLOCANDO APENAS POR MOTIVOS DE TESTE";

    for (int i = 0; i < 10; i++) {
        file.put(msg[i]);
    }
}

void test_timestamp() {
    boost::posix_time::ptime time = boost::posix_time::second_clock::local_time();
    std::cout << boost::posix_time::to_iso_string(time) << std::endl;
}

void test_files_needed() {
    std::string str = "QWERT";

    float str_size = str.size();
    float _max_size = 10;
    std::cout << ceil(str_size / _max_size) << std::endl;
}

int main() {
    test_files_needed();
}