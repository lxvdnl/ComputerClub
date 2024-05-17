#include <iostream>

#include "ComputerClubHandler.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Data file was not found\n";
        return 1;
    }

    std::string filename = argv[1];
    ComputerClubHandler handler(filename);
    handler.eventHandling();

    return 0;
}
