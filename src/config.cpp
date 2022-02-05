#include <config.hpp>

socksave::Config * socksave::read_config(std::string path) {
    Config * config = new Config();

    if (boost::filesystem::exists(path)) {
        boost::property_tree::ptree root;
        boost::property_tree::read_json(path, root);

        config->port         = root.get<int>("port", DEFAULT_PORT);
        config->timeout      = root.get<int>("timeout", DEFAULT_TIMEOUT);
        config->max_size     = root.get<int>("max_size", DEFAULT_SIZE);
        config->path         = root.get<std::string>("path", DEFAULT_DIR);
        config->prefix       = root.get<std::string>("prefix", DEFAULT_PREFIX);
    }
    else {
        config->port         = DEFAULT_PORT;
        config->timeout      = DEFAULT_TIMEOUT;
        config->max_size     = DEFAULT_SIZE;
        config->path         = DEFAULT_DIR;
        config->prefix       = DEFAULT_PREFIX;
    }
    
    return config;
}
