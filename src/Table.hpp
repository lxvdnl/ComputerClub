#pragma once
#ifndef __TABLE_HPP__
#define __TABLE_HPP__

#include <string>

#include "Time.hpp"

class Table {
    bool occupied;
    std::string client;
    Time tableOccupancyTime;
    Time startOfUse;
    size_t revenueHours;

   public:
    Table();
    void takeTable(std::string client, Time startTime);
    void clearTable(Time endTime);
    bool isOccupied() const;
    Time getTableOccupancyTime() const;
    size_t getRevenueHours() const;
};

#endif  // __TABLE_HPP__
