#ifndef DateTime_H
#define DateTime_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>  
#include <fstream>

class DateTime {
private:
    int hour;
    int minute;
public:
    DateTime(int h, int mi):  hour(h), minute(mi){}
    
    void SetHour(int h) { hour = h; }
    void SetMinute(int mi) { minute = mi; }   
    int GetHour() const { return hour; }
    int GetMinute() const { return minute; }
    std::string toStr() const {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hour << ":"
           << std::setfill('0') << std::setw(2) << minute;
        return ss.str();
    }

    void StoreTime(const std::string& filename) const {
        std::ofstream file(filename, std::ios::app); 
        if (file.is_open()) {
            file << hour << ":" << minute << std::endl;
            file.close();
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
}
};
class TimeRange {
private:
    DateTime startTime;
    DateTime endTime;

public:
    TimeRange(const DateTime& start, const DateTime& end) : startTime(start), endTime(end) {}

    void SetStartTime(const DateTime& start) { startTime = start; }
    void SetEndTime(const DateTime& end) { endTime = end; }
    DateTime GetStartTime() const { return startTime; }
    DateTime GetEndTime() const { return endTime; }
     std::string toStr() const {
        return "From " + startTime.toStr() + " To " + endTime.toStr();
    }
};

#endif // DateTime_H