#ifndef Booking_H
#define Booking_H


#include <string>
#include <iostream>
#include "DateTime.h"

enum class BookingStatus { Pending, Confirmed, Cancelled, Completed };

class Booking {
private:
    std::string bookingId;
    DateTime bookingTime;
    Member* bookingMember;
    Member* offeringMember;
    BookingStatus status;
    bool hasBeenRated;

public:
    Booking(std::string id, DateTime bookingTime, Member* bookingMem, Member* offeringMem,BookingStatus status)
        : bookingId(id), bookingTime(bookingTime), bookingMember(bookingMem), offeringMember(offeringMem), status(BookingStatus::Pending), hasBeenRated(false) {}
    virtual ~Booking() {}
    bool isMemberInvolved(const Member* member) const;
    std::string toCSV() const;
    std::string GetBookingId() const {
        return bookingId;
    }
    DateTime GetBookingTime() const {
        return bookingTime;
    }
    Member* GetBookingMember() const {
        return bookingMember;
    }
    Member* GetOfferingMember() const {
        return offeringMember;
    }
    BookingStatus GetStatus() const {
        return status;
    }
    bool HasBeenRated() const {
        return hasBeenRated;
    }
    bool isCompleted() const {
    return status == BookingStatus::Completed;
    }
    
    void CreateBooking();
    void CancelBooking();
    void CompleteBooking();
    void submitRating();
};
class BookingDatabase {
private:
    std::vector<Booking> bookings;
public:
void addBooking(const Booking& booking);
void saveToFile(const std::string& filename);
};

#endif // Booking_H