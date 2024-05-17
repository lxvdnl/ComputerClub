#include "Table.hpp"

Table::Table()
    : occupied(false),
      client(""),
      tableOccupancyTime(Time()),
      startOfUse(Time()),
      revenueHours(0) {}

bool Table::isOccupied() const { return occupied; }

void Table::takeTable(std::string client, Time startTime) {
    this->client = client;
    startOfUse = startTime;
    occupied = true;
}

void Table::clearTable(Time endTime) {
    client = "";
    occupied = false;
    tableOccupancyTime += endTime - startOfUse;
    revenueHours += ((endTime - startOfUse).minutes == 0)
                        ? (endTime - startOfUse).hours
                        : (endTime - startOfUse).hours + 1;
    startOfUse = Time();
}

Time Table::getTableOccupancyTime() const { return tableOccupancyTime; }
size_t Table::getRevenueHours() const { return revenueHours; }
