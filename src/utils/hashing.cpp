#include "core/hashing.hpp"
#include <functional>
#include "utils/hashing.hpp"

namespace mgit {

std::string generateHash(const std::string& content) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(content)); // basic hash for now
}

}

std::string sha1(const std::string& input) {
    std::hash<std::string> hasher;
    size_t hash_val = hasher(input);
    return std::to_string(hash_val); // crude but unique-ish
}
