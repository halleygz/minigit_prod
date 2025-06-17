#include <iostream>
#include <string>


int initCommand();

int main(int argc, char *argv[])
{
    
    if (argc < 2)
    {
        std::cout << "Usage: minigit <command>\n";
        return 1;
    }
    
    std::string command = argv[1];
    //temp debg script
    std::cout << "Command received: " << command << "\n";
    if (command == "init")
    {
        return initCommand();
    }

    std::cout << "Unknown command: " << command << "\n";
    return 1;
}