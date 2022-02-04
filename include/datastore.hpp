#ifndef __DATA_STORE_HPP__ 
#define __DATA_STORE_HPP__

#include <iostream>
#include <boost/filesystem.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"


namespace socksave {

class DataStore {
    public:
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

} // socksave

#endif