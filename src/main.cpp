#include <iostream> 

#include <datastore.hpp>
#include <server.hpp>
#include <config.hpp>

int main() {
    using namespace socksave;

    Config * config = read_config("config.json");

    LogServer server(config);
    server.run();

    delete config;
}