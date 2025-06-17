#include "core/file_io.hpp"
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filepath) {
    std::ifstream in(filepath);
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}
