#pragma once
#ifndef __COMPUTER_CLUB_HANDLER_HPP__
#define __COMPUTER_CLUB_HANDLER_HPP__

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Table.hpp"
#include "Time.hpp"

class ComputerClubHandler {
    size_t tablesNum;
    Time startTime, endTime;
    size_t costPerHour;
    std::vector<std::string> events;
    std::unordered_map<std::string, size_t>
        clients;  // Map of clients in the club and the tables at which they sit
    std::unordered_map<size_t, Table> tables;
    std::queue<std::string> waitingQueue;
    std::unordered_set<size_t> tablesOcupied;

   public:
    ComputerClubHandler(std::string filename);  // Reads and processes data
    void eventHandling();                       // Data generation
};

#endif  // __COMPUTER_CLUB_HANDLER_HPP__
