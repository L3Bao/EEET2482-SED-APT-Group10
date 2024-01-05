#ifndef BOOKING_H
#define BOOKING_H

#include "DateTime.h"
#include "Member.h"
#include <string>
#include <iostream>

class BookingDatabase; 

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
    Booking(std::string id, DateTime bookingTime, Member* bookingMem, Member* offeringMem)
        : bookingId(id), bookingTime(bookingTime), bookingMember(bookingMem), offeringMember(offeringMem), status(BookingStatus::Pending), hasBeenRated(false) {}

    virtual ~Booking() {}

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

    void CreateBooking();

    void CancelBooking();

    void CompleteBooking();

    void PrintBookingDetails() const;
};

#endif // BOOKING_H