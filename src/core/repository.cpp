#include "core/repository.hpp"
#include "core/blob.hpp"
#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace mgit
{
    void Repository::init()
    {
        try
        {
            if (fs::exists(".minigit"))
            {
                std::cout << "Repository already initialized.\n";
                return;
            }

            fs::create_directories(".minigit/branches");
            fs::create_directories(".minigit/commits");
            fs::create_directories(".minigit/blobs");

            std::ofstream(".minigit/HEAD") << "main";
            std::ofstream(".minigit/branches/main") << "";
            std::ofstream(".minigit/staging_area.json") << "{}";

            std::cout << "Initialized empty miniGit repository.\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error initializing repository: " << e.what() << '\n';
        }
    }

    void Repository::add(const std::string &file)
    {
        if (!fs::exists(file))
        {
            std::cerr << "File not found: " << file << "\n";
            return;
        }

        std::string blob_hash = Blob::create(file);

        json staging;
        std::ifstream in(".minigit/staging_area.json");
        if (in)
            in >> staging;

        staging[file] = blob_hash;

        std::ofstream out(".minigit/staging_area.json");
        out << staging.dump(4);

        std::cout << "Added " << file << " to staging area.\n";
    }
}