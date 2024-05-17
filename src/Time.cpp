#include "Time.hpp"

Time::Time() : hours(0), minutes(0) {}

Time::Time(const std::string& timeStr) {
    size_t colonPos = timeStr.find(':');
    if (colonPos != std::string::npos) {
        hours = std::stoi(timeStr.substr(0, colonPos));
        minutes = std::stoi(timeStr.substr(colonPos + 1));
        if (hours > 23 || minutes > 59) {
            std::cerr << "Invalid time: hours must be between 0 and 23, "
                         "minutes must be between 0 and 59"
                      << std::endl;
            hours = 0;
            minutes = 0;
        }
    } else {
        std::cerr << "Invalid time format" << std::endl;
        hours = 0;
        minutes = 0;
    }
}

bool Time::operator<(const Time& other) const {
    if (hours < other.hours)
        return true;
    else if (hours == other.hours && minutes < other.minutes)
        return true;
    else
        return false;
}

bool Time::operator>(const Time& other) const {
    return !(*this < other || *this == other);
}

bool Time::operator<=(const Time& other) const {
    return (*this < other || *this == other);
}

bool Time::operator>=(const Time& other) const { return !(*this < other); }

bool Time::operator==(const Time& other) const {
    return (hours == other.hours && minutes == other.minutes);
}

bool Time::operator!=(const Time& other) const { return !(*this == other); }

std::istream& operator>>(std::istream& is, Time& time) {
    char ch;
    is >> time.hours >> ch >> time.minutes;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << (time.hours < 10 ? "0" : "") << time.hours << ":"
       << (time.minutes < 10 ? "0" : "") << time.minutes;
    return os;
}

Time Time::operator+(const Time& other) {
    Time result;
    result.hours = hours + other.hours;
    result.minutes = minutes + other.minutes;
    if (result.minutes >= 60) {
        result.hours += result.minutes / 60;
        result.minutes %= 60;
    }
    return result;
}

Time Time::operator-(const Time& other) {
    Time result;
    if (*this >= other) {
        result.hours = hours - other.hours;
        if (minutes >= other.minutes) {
            result.minutes = minutes - other.minutes;
        } else {
            result.minutes = 60 + minutes - other.minutes;
            result.hours--;
        }
    }
    return result;
}

Time& Time::operator=(const Time& other) {
    if (this != &other) {
        hours = other.hours;
        minutes = other.minutes;
    }
    return *this;
}

Time& Time::operator+=(const Time& other) {
    *this = *this + other;
    return *this;
}

Time& Time::operator-=(const Time& other) {
    *this = *this - other;
    return *this;
}
