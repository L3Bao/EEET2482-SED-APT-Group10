#include "DateTime.h"
#include <iostream>


void DateTime::setStartTime(int hour, int minute) {
        startHour = hour;
        startMinute = minute;
    }

    
    void DateTime::setEndTime(int hour, int minute) {
        endHour = hour;
        endMinute = minute;
    }

    
    std::string DateTime::getStartTime() const {
        return formatTime(startHour, startMinute);
    }

    std::string DateTime::getEndTime() const {
        return formatTime(endHour, endMinute);
    }

    
    std::string DateTime::formatTime(int hour, int minute) const {
        std::ostringstream stream;
        stream << std::setfill('0') << std::setw(2) << hour << ':'
               << std::setw(2) << minute;
        return stream.str();
    }

    // Function to get the full range as a string
    std::string DateTime::getTimeRange() const {
        return "From " + getStartTime() + " to " + getEndTime();
    }

int main() {
    std::string startTime, endTime;
    int startHour, startMinute, endHour, endMinute;

    // Prompting user for start time
    std::cout << "Enter start time (hh:mm): ";
    std::getline(std::cin, startTime);
    std::stringstream startStream(startTime);
    startStream >> startHour;
    startStream.ignore(1); 
    startStream >> startMinute;

    // Prompting user for end time
    std::cout << "Enter end time (hh:mm): ";
    std::getline(std::cin, endTime);
    std::stringstream endStream(endTime);
    endStream >> endHour;
    endStream.ignore(1); 
    endStream >> endMinute;

    // Create a DateTime object with user-provided times
    DateTime bookingTime(startHour, startMinute, endHour, endMinute);

    // Print the time range
    std::cout << "Availability time: " << bookingTime.getTimeRange() << std::endl;
   return 0;
}


