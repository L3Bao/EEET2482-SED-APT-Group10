#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <User.h>
#include <service.h>

class Booking;
class Member;
class Admin;
class Rating;

class System {
private:
    std::vector<User*> userList;
    std::vector<Service*> serviceList;
    std::vector<Booking*> bookingList;
    std::vector<Rating*> ratingList;
    std::vector<Member*> blockedList;

public:
    std::vector<User*> userList;
    std::vector<Service*> serviceList;
    std::vector<Booking*> bookingList;
    std::vector<Rating*> ratingList;
    std::vector<Member*> blockedList;
    
    System();

    ~System();

    void HandleRegistration();
    void TopUpCredits();
    void SearchServices();
    void FilterServices();
};


#endif