#include <iostream>
#include <fstream>
#include <limits>

void correctPath(std::string& path) {
    std::ifstream file(path);
    while (!file.is_open()) {
        std::cout << "Invalid path! Try again:" << std::endl;
        std::getline(std::cin, path);
    }
}

int main() {
    char choice;
    do {
        std::cout << "1 - see file content; 2 - write something down: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice != '1' && choice != '2') {
            std::cout << "Please enter 1 or 2" << std::endl;
        } 
    } while (choice != '1' && choice != '2');

    if (choice == '1') {
        std::string path;
        std::cout << "Path: ";
        std::getline(std::cin, path);
        correctPath(path);

        std::ifstream file(path, std::ios::binary);

        char buffer[1025];
        while (file.read(buffer, 1024)) {
            buffer[file.gcount()] = '\0';
            std::cout << buffer;
        }
        buffer[file.gcount()] = '\0';
        std::cout << buffer << std::endl;

        file.close();
    } else if (choice == '2') {
        std::string path;
        std::cout << "Path: ";
        std::getline(std::cin, path);
        correctPath(path);

        std::ofstream file(path, std::ios::app);
        
        std::string text;
        std::cout << "To stop write :q next line:" << std::endl;
        std::getline(std::cin, text);

        while (text != ":q") {
            file << text << std::endl;
            std::getline(std::cin, text);
        }

        file.close();
    }
    return 0;
}