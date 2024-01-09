#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include <vector>
#include <set>
#include <stdio.h>
#include "User.h"
#include "DateTime.h"
#include <iostream>
#include "Service.h"
#include "Booking.h"
#include "Rating.h"


class Member: public User {
    int memberID;
    std::string name;
    std::string phoneNumber;
    std::string email;
    std::string address;
    std::set<std::string> blockedMembers;
    std::string city;
    int creditPoints;

    Skill *ownedSkills;

    std::vector<Rating*> memberRatingList;
    std::vector<Request*> memberRequestList;

    public:
    Member(int memberID, std::string username, std::string password, std::string name, std::string phoneNumber, std::string email, std::string address, std::string city, int creditPoints = 20);

    double getRatingScore();

    bool showMemberProfile();

    bool listSkill(DateTime *startTime, DateTime *endTime, int creditCostPerHour, double minHostRating);

    bool unlistSkill();

    bool showListOfRequest();

    bool denyRequest(int requestID);

    bool acceptRequest(int requestID);

    bool finishSupport(int skillID);

    bool reviewSkillAndSupporter(Skill *supportedSkill, int skillRating, int supporterRating, std::string comment);

    bool reviewHost(int reviewedHostID, int hostRating, std::string comment);
        
 
};
#endif