
#ifndef DateTime_H
#define DateTime_H
#include <sstream>
#include <iomanip>

class DateTime {
private:
    int startHour, startMinute; // Start time
    int endHour, endMinute;     // End time

public:
    
    DateTime(int sh = 0, int sm = 0, int eh = 0, int em = 0);

    
    void setStartTime(int hour, int minute);
    void setEndTime(int hour, int minute);

    
    std::string getStartTime() const;
    std::string getEndTime() const;

    std::string formatTime(int hour, int minute) const;

    
    std::string getTimeRange() const;
};


#endif // DATETIME_H
