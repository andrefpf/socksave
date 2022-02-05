#include <datastore.hpp>
#include <utils.hpp>

socksave::DataStore::DataStore(int max_size, boost::filesystem::path path, std::string prefix="") {
    _files_needed = 0;
    _size = max_size;
    _max_size = max_size;
    _prefix = prefix;
    _path = path;
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

void socksave::DataStore::close() {
    _current_file.flush();
    _current_file.close();
}

void socksave::DataStore::create_file() {
    std::string filename;

    if (!boost::filesystem::is_directory(_path)) {
        boost::filesystem::create_directories(_path);
    } 
    
    filename  = _prefix;
    filename += "_" + get_timestamp();
    filename += "_" + std::to_string(_files_needed);

    _current_file.close();
    _current_file.open(_path / filename, std::ios_base::app);

    _files_needed++;
    _size = 0;
}
