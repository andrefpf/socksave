#include <iostream> 

#include <datastore.hpp>
#include <server.hpp>


int main() {
    using namespace socksave;

    LogServer server(1234, 20, "output", "PREFIX");
    server.run();
}