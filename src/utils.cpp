#include <utils.hpp>


std::string socksave::get_timestamp() {
    boost::posix_time::ptime time = boost::posix_time::second_clock::local_time();
    return boost::posix_time::to_iso_string(time);
}
