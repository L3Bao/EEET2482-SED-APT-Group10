#ifndef BOOKINGDATABASE_H
#define BOOKINGDATABASE_H

#include <unordered_map>
#include <string>
#include "Booking.h"  

class BookingDatabase {
private:
    std::unordered_map<std::string, Booking> bookings;
    static BookingDatabase* instance;

    // Private Constructor
    BookingDatabase() {}

public:
    
    static BookingDatabase* GetInstance() {
        if (instance == nullptr) {
            instance = new BookingDatabase();
        }
        return instance;
    }

    void StoreBooking(const Booking& booking) {
        bookings[booking.GetBookingId()] = booking;
    }

    
};


BookingDatabase* BookingDatabase::instance = nullptr;

#endif // BOOKINGDATABASE_H
