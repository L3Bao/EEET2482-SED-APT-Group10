#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <User.h>
#include <service.h>

class Booking;
class Member;
class Rating;

class System {
private:
    std::vector<User*> userList;
    std::vector<Service*> serviceList;
    std::vector<Booking*> bookingList;
    std::vector<Rating*> ratingList;
    std::vector<Member*> blockedList;

public:
    System(std::vector<User*> users = {}, std::vector<Service*> services = {}, std::vector<Booking*> bookings = {}, std::vector<Rating*> reviews = {}, std::vector<Member*> blockedMembers = {}) : userList(users), serviceList(services), bookingList(bookings), ratingList(reviews), blockedList(blockedMembers) {}

    ~System();

    void HandleRegistration();
    void TopUpCredits();
    void SearchServices();
    void FilterServices();
};


#endif