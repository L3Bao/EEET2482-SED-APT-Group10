
#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include <vector>
#include <stdio.h>
#include "User.h"
#include "DateTime.h"
#include <iostream>
#include "Service.h"
#include "Booking.h"
#include "Rating.h"
using namespace std;


class Service;
class Member: public User {
    public:
    //Constructors
        Member(string userId, string username, string password, string contact, string address);
        Member(string userId, string username, string password, string contact, string address , vector<string> skills, float requiredHostRating, vector<Member*> blockedMembers, float averageHostRating, float averageSupporterRating, string city, int creditPoints);
        
        //Getters and Setters
        string getAddress();
        vector<string> getSkills();
        float getRequiredHostRating();
        vector<Member*> getBlockedMembers();
        float getAverageHostRating();
        float getAverageSupporterRating();
        string getCity();
        int getCreditPoints();
        void setAddress(string address);
        void setSkills(vector<string> skills);
        void setRequiredHostRating(float requiredHostRating);
        void setBlockedMembers(vector<Member*> blockedMembers);
        void setAverageHostRating(float averageHostRating);
        void setAverageSupporterRating(float averageSupporterRating);
        void setCity(string city);
        void setCreditPoints(int creditPoints);
        void toString();

        //Methods
        void blockMember(Member* member);
        void unblockMember(Member* memberToUnblock);
        void viewRequests(vector<Service*> serviceList);
        void acceptRequest(Service* service);
        void updateSkills();
        void calculateAverageHostRating(vector<Rating *> ratingList);
        void calculateAverageSupporterRating(vector<Rating *> ratingList);
        friend class Service;

    private:
    //Attributes
        vector<string> skills;
        float requiredHostRating;
        vector<Member*> blockedMembers;
        float averageHostRating;
        float averageSupporterRating;
        string city;
        int creditPoints;
};
#endif