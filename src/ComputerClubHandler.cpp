#include "ComputerClubHandler.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

ComputerClubHandler::ComputerClubHandler(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file >> tablesNum;
    if (tablesNum <= 0) {
        std::cerr << "Invalid value for tables num: " << tablesNum << std::endl;
        file.close();
        return;
    }

    for (size_t i = 1; i <= tablesNum; ++i) {
        tables.insert(std::make_pair(i, Table()));
    }

    std::string line;
    std::getline(file, line);  // Skip '\n'
    std::getline(file, line);
    std::istringstream iss(line);
    iss >> startTime >> endTime;

    if (startTime >= endTime) {
        std::cerr << "Start time is not before end time" << std::endl;
        file.close();
        return;
    }

    file >> costPerHour;
    if (costPerHour <= 0) {
        std::cerr << "Invalid value for cost per hour: " << costPerHour
                  << std::endl;
        file.close();
        return;
    }

    std::getline(file, line);  // Skip '\n'
    while (std::getline(file, line)) events.push_back(line);

    file.close();
}

void ComputerClubHandler::eventHandling() {
    std::vector<std::string> tokens;
    std::cout << startTime << std::endl;

    // Traversing events
    for (auto line : events) {
        std::cout << line << std::endl;
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) tokens.push_back(token);

        // Switch by events id
        switch (std::stoi(tokens[1])) {
            case 1:
                if (tokens.size() != 3) {
                    std::cerr << "Invalid number of arguments for event\n";
                    return;
                }
                if (Time(tokens[0]) < startTime || Time(tokens[0]) > endTime)
                    std::cout << tokens[0] << " 13 NotOpenYet\n";
                else if (clients.find(tokens[2]) != clients.end())
                    std::cout << tokens[0] << " 13 YouShallNotPass\n";
                // If everything is fine, then add the client to the list of
                // clients and give the table number 0 (no table yet)
                else {
                    clients.insert(std::make_pair(tokens[2], 0));
                }
                break;
            case 2:
                if (tokens.size() != 4) {
                    std::cerr << "Invalid number of arguments for event\n";
                    return;
                }
                if (std::stoi(tokens[3]) > tablesNum) {
                    std::cout << tokens[0] << " 13 ThereIsNoSuchTable\n";
                    break;
                }
                // The table is occupied
                if (tables[std::stoi(tokens[3])].isOccupied())
                    std::cout << tokens[0] << " 13 PlaceIsBusy\n";
                // The client is not in the club
                else if (clients.find(tokens[2]) == clients.end())
                    std::cout << tokens[0] << " 13 ClientUnknown\n";
                else {
                    // The client just sat down
                    if (clients[tokens[2]] == 0) {
                        clients[tokens[2]] = std::stoi(tokens[3]);
                        tables[std::stoi(tokens[3])].takeTable(tokens[2],
                                                               Time(tokens[0]));
                    }
                    // The client moved
                    else {
                        tables[clients[tokens[2]]].clearTable(tokens[0]);
                        clients[tokens[2]] = std::stoi(tokens[3]);
                        tables[std::stoi(tokens[3])].takeTable(tokens[2],
                                                               Time(tokens[0]));
                    }
                    tablesOcupied.insert(std::stoi(tokens[3]));
                }
                break;
            case 3:
                if (tokens.size() != 3) {
                    std::cerr << "Invalid number of arguments for event\n";
                    return;
                }
                // If the queue is full, then call event 11
                if (waitingQueue.size() >= tablesNum) {
                    std::cout << tokens[0] << " 11 " << tokens[2] << std::endl;
                    clients.erase(tokens[2]);
                }
                // If there are free tables we issue event 13
                if (tablesOcupied.size() != tablesNum) {
                    std::cout << tokens[0] << " 13 ICanWaitNoLonger!\n";
                    break;
                } else
                    waitingQueue.push(tokens[2]);
                break;
            case 4:
                if (tokens.size() != 3) {
                    std::cerr << "Invalid number of arguments for event\n";
                    return;
                }
                // The client is not in the club
                if (clients.find(tokens[2]) == clients.end())
                    std::cout << tokens[0] << " 13 ClientUnknown\n";
                else {
                    // If the client is not at the table, then we simply remove
                    // him
                    if (clients[tokens[2]] == 0) clients.erase(tokens[2]);
                    // If there are clients in the queue, then we seat the first
                    // client at the vacant table
                    else if (!waitingQueue.empty()) {
                        std::string clientName = waitingQueue.front();
                        waitingQueue.pop();
                        size_t tableN = clients[tokens[2]];
                        std::cout << tokens[0] << " 12 " << clientName << " "
                                  << tableN << std::endl;
                        tables[tableN].clearTable(Time(tokens[0]));
                        tables[tableN].takeTable(clientName, Time(tokens[0]));
                        clients.erase(tokens[2]);
                        clients[clientName] = tableN;
                    }
                    // If the queue is empty, just clear the table
                    else {
                        size_t tableN = clients[tokens[2]];
                        tables[tableN].clearTable(Time(tokens[0]));
                        clients.erase(tokens[2]);
                        tablesOcupied.erase(tableN);
                    }
                }
                break;
            default:
                std::cerr << "No such event ID exists\n";
                return;
        }

        tokens.clear();
    }

    // Traversing clients remaining in the club
    for (auto client : clients) {
        if (client.second)
            std::cout << endTime << " 11 " << client.first << std::endl;
    }
    std::cout << endTime << std::endl;

    // Traversing tables and conclusion revenue
    for (auto table : tables) {
        if (table.second.isOccupied()) table.second.clearTable(endTime);
        std::cout << table.first << " "
                  << table.second.getRevenueHours() * costPerHour << " "
                  << table.second.getTableOccupancyTime() << std::endl;
    }
}
