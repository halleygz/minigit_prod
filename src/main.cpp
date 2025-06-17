#include <iostream>
#include <string>


int initCommand();
int addCommand(const std::string& filename);

int main(int argc, char *argv[])
{
    
    if (argc < 2)
    {
        std::cout << "Usage: minigit <command>\n";
        return 1;
    }
    
    std::string command = argv[1];
    if (command == "init")
    {
        return initCommand();
    } else if (command == "add"){
        if(argc < 3) {
            std::cerr<< "Usage: minigit add <file>\n";
            return 1;
        }

        return addCommand(argv[2]);
    }


    std::cout << "Unknown command: " << command << "\n";
    return 1;
}