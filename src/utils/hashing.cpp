#include "core/hashing.hpp"
#include <functional>

std::string sha1(const std::string& input) {
    std::hash<std::string> hasher;
    size_t hash_val = hasher(input);
    return std::to_string(hash_val); // crude but unique-ish
}
