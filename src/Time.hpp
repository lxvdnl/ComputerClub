#pragma once
#ifndef __TIME_HPP__
#define __TIME_HPP__

#include <iostream>
#include <string>

struct Time {
    size_t hours;
    size_t minutes;

    Time();
    Time(const std::string& timeStr);

    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;

    Time operator+(const Time& other);
    Time operator-(const Time& other);
    Time& operator=(const Time& other);
    Time& operator+=(const Time& other);
    Time& operator-=(const Time& other);
};

std::istream& operator>>(std::istream& is, Time& time);
std::ostream& operator<<(std::ostream& os, const Time& time);

#endif  // __TIME_HPP__
