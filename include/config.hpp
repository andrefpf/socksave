#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

const int DEFAULT_PORT              = 1234;
const int DEFAULT_TIMEOUT           = 10;
const int DEFAULT_SIZE              = 1024;
const std::string DEFAULT_DIR       = "output/";
const std::string DEFAULT_PREFIX    = "PREFIX";

namespace socksave {

struct Config {
    int port;
    int max_size;
    int timeout;
    std::string path;
    std::string prefix;
};

Config * read_config(std::string path);

} // socksave

#endif