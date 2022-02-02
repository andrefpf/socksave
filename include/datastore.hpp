#ifndef __SAVER_HPP__ 
#define __SAVER_HPP__

#include <iostream>
// #include <boost/asio.hpp>
#include <boost/filesystem/fstream.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"


namespace socksave {

class DataStore {
    public:
        DataStore(int max_size, boost::filesystem::path dir);
        DataStore(int max_size, boost::filesystem::path dir, std::string prefix);

        void write(std::string str);
    
    private:
        void create_file();
        std::string get_timestamp();
    
    private:
        int _size;
        int _max_size;
        int _files_needed;
        std::string _prefix;
        boost::filesystem::path _dir;
        boost::filesystem::ofstream _current_file;
};

}

#endif