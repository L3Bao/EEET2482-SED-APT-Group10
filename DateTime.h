
#ifndef DateTime_H
#define DateTime_H
#include <sstream>
#include <iomanip>

class DateTime {
    int hour, minute;

public:
    
    DateTime();
    DateTime(int hour, int minute);

    // Operator to compare time range
    bool operator<(DateTime &other);

    // Operator to find the difference between two time range
    int operator-(DateTime &other);
    
    std::string toString();
};


#endif // DATETIME_H
