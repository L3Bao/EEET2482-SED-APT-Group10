#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>
#include <iomanip>

class DateTime {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:
    DateTime() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

    
    DateTime(int y, int mo, int d, int h, int mi, int s)
        : year(y), month(mo), day(d), hour(h), minute(mi), second(s) {}

    
    void SetYear(int y) { year = y; }
    void SetMonth(int mo) { month = mo; }
    void SetDay(int d) { day = d; }
    void SetHour(int h) { hour = h; }
    void SetMinute(int mi) { minute = mi; }
    void SetSecond(int s) { second = s; }

    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }
    int GetHour() const { return hour; }
    int GetMinute() const { return minute; }
    int GetSecond() const { return second; }

    // Display Function
    void Display() const {
         std::cout << std::setfill('0') << std::setw(4) << year << "-"
                  << std::setfill('0') << std::setw(2) << month << "-"
                  << std::setfill('0') << std::setw(2) << day << " "
                  << std::setfill('0') << std::setw(2) << hour << ":"
                  << std::setfill('0') << std::setw(2) << minute << ":"
                  << std::setfill('0') << std::setw(2) << second << std::endl;
    }
    };

    

#endif // DATETIME_H
