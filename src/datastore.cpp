#include <datastore.hpp>


socksave::DataStore::DataStore(int max_size, boost::filesystem::path dir, std::string prefix="") {
    _files_needed = 0;
    _size = max_size;
    _max_size = max_size;
    _prefix = prefix;
    _dir = dir;
}

void socksave::DataStore::write(std::string str) {
    int str_size = str.size();

    for (int i = 0; i < str_size; i++, _size++) {
        if (_size >= _max_size) {
            create_file();
        }
        _current_file.put(str[i]);
    }
}

void socksave::DataStore::create_file() {
    std::string filename;
    
    filename  = _prefix;
    filename += "_" + std::to_string(_files_needed);
    filename += "_" + get_timestamp();

    _current_file.close();
    _current_file.open(_dir / filename, std::ios_base::app);

    _files_needed++;
    _size = 0;
}

std::string socksave::DataStore::get_timestamp() {
    boost::posix_time::ptime time = boost::posix_time::second_clock::local_time();
    return boost::posix_time::to_iso_string(time);
}
