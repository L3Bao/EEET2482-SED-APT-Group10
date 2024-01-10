#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <iostream>
#include "User.h"
#include "InputCheck.h"

class Skill;
class Member;
class Admin;
class DateTime;
class InputCheck;

class System {

public:
    std::vector<Member*> memberList;
    std::vector<Skill*> skillList;
    std::vector<Skill*> memberAvailableSkillList;
    std::vector<Admin*> adminList;
    Member* currentMem;
    InputCheck ic;

    System();

        void setCurrentMember(Member *member);

    void clearScreen();

    void highlighter();

    void addMember(Member *member);

    void addMotorbike(Motorbike *motorbike);

    void addAdmin(Admin *admin);

    bool memberLogin();

    bool memberSearchSuitableMotorbikeList(Date *startDate, Date *endDate, int cityID);

    bool isSuitableMotorbike(Date *startDate, Date *endDate, int cityID, Motorbike *motorbike);

    bool memberSendRequest(Date *startDate, Date *endDate, int motorbikeID);

    bool memberSeeRequestList();

    bool memberAcceptRequest(int requestID);

    bool memberViewRentList();

    bool turnbackMotorbike(int turnbackRentMotorbikeID);

    bool memberViewUnratedRenterList();

    bool memberRateRenter(int renterID);

    bool memberRateMotorbike(Motorbike* ratedMotorbike);

    void mainMenu();

    void adminMenu();

    bool adminLogin();

    void adminViewMemberList();

    void adminViewMotorbikeList();

    void memberMenu();

    void memberLoginMenu();

    bool memberRegister();

    void memberListMenu();

    bool memberListMotorbike();

    bool memberUnlistMotorbike();

    void memberSearchSuitableMotorbikeMenu();

    void memberSuitableMotorbikeMenu(Date *sD, Date *eD, int cityID);

    void memberViewMotorbikeRequestList(int motorbikeID);

    bool memberViewMotorbikeReviewList(int motorbikeID, Date *sD, Date *eD);

    void memberUnratedRenterRatingMenu(int member);

    void memberViewRentedMotorbike();

    bool memberLeaveReview(Motorbike *turnbackMotorbike);

    bool memberEnterMotorbikeInfo();

    void guestMenu();

    void guestViewMotorbikeList();

    void UnrateMemRatingMenu();

    void memberViewMotorbikeRequestListMenu();

    void suitableMotorbikeMenu(int choice, Date *sD, Date *eD, int cityID);

    void memberViewRenterReviewList(int choice);

    int choiceFunc(int a, int b);

    void systemExit();

    friend class InputStorageManager;

    friend class OutputStorageManager;

};


#endif