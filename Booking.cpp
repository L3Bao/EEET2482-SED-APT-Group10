#include "Booking.h"         
#include "Member.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>





int main() {
    
    Member* bookingMember = new Member("MemberName1", 1); 
    Member* offeringMember = new Member("MemberName2", 2); 

    DateTime bookingTime(2023, 3, 15, 22, 0, 0);
    std::string bookingId = "123";
    Booking myBooking("123", bookingTime, bookingMember, offeringMember);

    std::cout << "Creating a booking..." << std::endl;
    myBooking.CreateBooking();
    std::cout << "Booking created." << std::endl;
    
    myBooking.PrintBookingDetails();
    delete bookingMember;
    delete offeringMember;

    return 0;
}
