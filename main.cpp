#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 3) {
        std::cerr << "Use:\n"
                  << "  " << argv[0] << " --read <file>\n"
                  << "  " << argv[0] << " --write <file>\n";
        return 1;
    }

    std::string command = argv[1];
    std::string path = argv[2];

    if (command == "--read") {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Invalid path: " << path << std::endl;
            return 1;
        }

        char buffer[1025];

        while (file) {
            file.read(buffer, 1024);
            std::streamsize count = file.gcount();
            if (count <= 0) break;

            buffer[count] = '\0';
            std::cout << buffer;
        }

        std::cout << std::endl;

        file.close();
    } else if (command == "--write") {
        std::ofstream file(path, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Invalid path: " << path << std::endl;
            return 1;
        }

        std::string text;
        std::cout << "Enter \":q\" on a new line to exit:" << std::endl;
        std::getline(std::cin, text);

        while (text != ":q") {
            file << text << std::endl;
            std::getline(std::cin, text);
        }

        file.close();
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }
    
    return 0;
}