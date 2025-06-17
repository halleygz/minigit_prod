#include "core/repository.hpp"
#include "core/commit.hpp"
#include "core/blob.hpp"
#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <chrono>

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace mgit
{
    std::string getCurrentTimeStamp();
    std::string generateHash(const std::string &content);

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

    int Repository::commit(const std::string &message)
    {
        std::string branch;
        std::ifstream("./minigit/HEAD") >> branch;

        std::string branch_path = "./minigit/branches/" + branch;
        std::ifstream branch_file(branch_path);
        std::string parent_commit;
        branch_file >> parent_commit;

        std::ifstream staging(".minigit/staging_area.json");
        json staged_files_json;
        staging >> staged_files_json;

        std::map<std::string, std::string> files;
        for (auto &[fname, blob] : staged_files_json.items())
        {
            files[fname] = blob;
        }

        Commit commit;
        commit.parent = parent_commit;
        commit.message = message;
        commit.timestamp = getCurrentTimeStamp();
        commit.files = files;

        std::string content = commit.serialize();
        commit.hash = generateHash(content);

        std::ofstream(".minigit/commits/" + commit.hash + ".json") << content;
        std::ofstream(branch_path) << commit.hash;

        std::ofstream(".minigit/staging_area.json") << "{}";
        std::cout << "Commited as " << commit.hash << "\n";
        return 0;
    }
}