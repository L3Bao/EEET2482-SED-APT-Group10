#include "DateTime.h"
#include "Member.h"
#include "Booking.h"
#include <iostream> 
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <sstream>


void Booking::CreateBooking() {
        if (bookingMember == nullptr || offeringMember == nullptr) {
            std::cout << "Booking cannot be created. Member information is incomplete." << std::endl;
            return;
        }  
        bookingTime.setCurrentTime();
        this->status = BookingStatus::Pending;
        this->hasBeenRated = false;
        std::cout << "Booking created successfully with ID: " << bookingId << std::endl;
    }
   void Booking::CancelBooking() {
    if (status != BookingStatus::Pending) {
        std::cout << "Booking cannot be cancelled as it is not in Pending status." << std::endl;
        return;
    }

    this->status = BookingStatus::Cancelled;
    std::cout << "Booking with ID: " << bookingId << " has been cancelled." << std::endl;
}
    void Booking::CompleteBooking() {
    if (status != BookingStatus::Pending) {
        std::cout << "Booking cannot be completed as it is not in Pending status." << std::endl;
        return;
    }
    status = BookingStatus::Completed;
    std::cout << "Booking with ID: " << bookingId << " has been completed." << std::endl;
}
   std::string Booking::toCSV() const {
    std::ostringstream csvStream;

    // Constructing date-time string
    csvStream << std::setfill('0') 
              << std::setw(4) << bookingTime.GetYear() << "-"
              << std::setw(2) << bookingTime.GetMonth() << "-"
              << std::setw(2) << bookingTime.GetDay() << " "
              << std::setw(2) << bookingTime.GetHour() << ":"
              << std::setw(2) << bookingTime.GetMinute() << ":"
              << std::setw(2) << bookingTime.GetSecond();

    // Adding booking details to the stream
    csvStream << bookingId << ","
              << csvStream.str() << ",";

    //get Member name
    csvStream << (bookingMember ? bookingMember->getUsername() : "N/A") << ","
              << (offeringMember ? offeringMember->getUsername() : "N/A") << ",";

    csvStream << static_cast<int>(status) << ","
              << (hasBeenRated ? "true" : "false");

    return csvStream.str();
}
    void Booking::submitRating(){
        if (!hasBeenRated) {
            hasBeenRated = true; 
        } else {
            std::cout << "This service has already been rated." << std::endl;
        }

    }

    bool Booking::isMemberInvolved(const Member* member) const {
        return (member == bookingMember || member == offeringMember);
}

    void BookingDatabase::addBooking(const Booking& booking) {
        bookings.push_back(booking);
}

    void BookingDatabase::saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing." << std::endl;
            return;
        }
        for (const auto& booking : bookings) {
            file << booking.toCSV();
        }
        file.close();
        std::cout << "Bookings saved to " << filename << std::endl;
    }

// int main() {
//   std::string bookingId;
//     BookingDatabase db;
//     std::time_t t = std::time(nullptr);
//     BookingStatus stat = BookingStatus::Pending;


//     Member* bookingMember = nullptr; 
//     Member* offeringMember = nullptr;

//     std::cout << "Welcome to the Booking System" << std::endl;
//     std::cout << "Enter booking ID: ";
//     std::cin >> bookingId;



//    DateTime bookingTime;
//     bookingTime.setCurrentTime();
//     // Create sample bookings and add to database
//    Booking booking(bookingId, bookingTime, bookingMember, offeringMember, stat);
//     db.addBooking(booking);
//     booking.CreateBooking();
//     booking.CancelBooking();
//     booking.CompleteBooking();
    
    
//     db.saveToFile("bookings.csv");
//     return 0;
// }
