#include <string>
#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

namespace mgit
{

    class Repository
    {
    public:
        static void init();
    public:
        static void add(const std::string& file);
    public:
        static int commit(const std::string& message);
    };
}

#endif