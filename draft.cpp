#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::getline;

//Global Variables for system
vector<Member*> Database;

//Help to load data
std::fstream data;
std::fstream listRequest;

class Review {
public:
    double skillRating;
    double supporterRating;
    std::string comment;

    Review(double skillRating, double supporterRating, std::string comment)
        : skillRating(skillRating), supporterRating(supporterRating), comment(comment) {}
};

//Class of Member
class Member
{
    private:
        string userName;
        string password;
        string fullName;
        string phoneNumber;
        string email;
        string HomeAddress;
        vector<string> skills;
        int creditPoint;
        double HostRatingScore_Avg;
        double SkillRatingScore_Avg;
        double SupporterRatingScore_Avg;
        vector<Member*> blockedMembers;
        vector<Review*> reviews;


        vector<Member*> listOfrequests;
        vector<Member*> listOfreviews;
    public:

    //Constructor
        Member(string userNameVal = "", string password_val = "", string fullname_val = "", string phonenumber_val = "",
               string email_val = "", string homeadress_val = "", vector<string> skills = {}, int creditpoint_val = 20,
               double HostRatingScore_AvgVal = 0, double SkillRatingScore_AvgVal = 0, double SupporterRatingScore_AvgVal = 0)
            : userName(userNameVal), password(password_val), fullName(fullname_val), phoneNumber(phonenumber_val), email(email_val),
              HomeAddress(homeadress_val), skills(skills), creditPoint(creditpoint_val), HostRatingScore_Avg(HostRatingScore_AvgVal),
              SkillRatingScore_Avg(SkillRatingScore_AvgVal), SupporterRatingScore_Avg(SupporterRatingScore_AvgVal) {}

    //Method

    void ShowInfo()
    {
        cout << "\nYour Information:\n";
        cout << "   Fullname = " << fullName << ". Username = " << userName << ". Password = " << password << "\n"
                << "   Phone number = " << phoneNumber << ".   Home Adress = " << HomeAddress << ".   Email = " << email << "\n"
                << "   Credit point = " << creditPoint << ".   Host Rating Score = " << HostRatingScore_Avg << ".\n"
                << "   Skill Rating Score = " << SkillRatingScore_Avg << ". Supporter-rating Score = " << SupporterRatingScore_Avg << "\n";
    }

    //LogIn feature should be in member class
    bool LogIn()
    {
        bool SuccessLog = false;
        bool SuccessUsername = false;
        int i = 0;
        int j = 0;
        string Input_UserName;
        string Input_Password;
        cout << "Enter username: ";
        cin >> Input_UserName;
        //Check the Input UserName is existed in Database
        for(auto each : Database)
        {
            i++;
            if(Input_UserName == each->userName)
            {

                SuccessUsername = true;
                cout << "Enter password: ";
                cin >> Input_Password;
                
                if(Input_Password == each->password)
                {
                    cout << "Log In Successfully!!\n";
                    fullName = each->fullName;
                    userName = each->userName;
                    phoneNumber = each->phoneNumber;
                    SkillRatingScore_Avg = each->SkillRatingScore_Avg;
                    HostRatingScore_Avg = each->HostRatingScore_Avg;
                    creditPoint = each->creditPoint;
                    password = each->password;

                    // //Load list of request
                    for(auto request : each->listOfrequests)
                    {
                        listOfrequests.push_back(request);
                    }

                    for(auto review : each->listOfreviews)
                    {
                        listOfreviews.push_back(review);
                    }

                    SuccessLog = true;
                    return true;
                }
            }
        
        }
        if(SuccessUsername == false)
        {
            cout << "Wrong Username\n";
            return false;
        }
        else
        {
            cout << "Wrong Password\n";
            return false;
        }

    }
    
    // Method to check if a member is blocked
        bool isBlocked(Member* member) {
            for(Member* blockedMember : blockedMembers) {
                if(blockedMember == member) {
                    return true;
                }
            }
            return false;
        }

    // Method to block a member
    void blockMember(Member* member) {
        blockedMembers.push_back(member);
    }

    // Method to calculate average ratings
    void calculateRatings() {
        double totalSkillRating = 0;
        double totalSupporterRating = 0;
        for(Review* review : reviews) {
            totalSkillRating += review->skillRating;
            totalSupporterRating += review->supporterRating;
        }
        SkillRatingScore_Avg = totalSkillRating / reviews.size();
        SupporterRatingScore_Avg = totalSupporterRating / reviews.size();
    }

    //Gain access
    friend class System;
    friend class Admin;
    
};

class TimeSlot {
public:
    string startTime;
    string endTime;
    string skill;
    int pointsPerHour;

    //Constructor
    TimeSlot(string startTime = "", string endTime = "", string skill = "", int pointsPerHour_val = 0)
        : startTime(startTime), endTime(endTime), skill(skill), pointsPerHour(pointsPerHour_val) {}
};

//Class Supporter inherited by class Member
class Supporter : public Member {
private:
    vector<TimeSlot*> availableTimeSlots;
    double minimumHostRating;

public:
    Supporter(string userNameVal = "", string password_val = "", string fullname_val = "", string phonenumber_val = "",
               string email_val = "", string homeadress_val = "", vector<string> skills = {}, int creditpoint_val = 20,
               double HostRatingScore_AvgVal = 0, double SkillRatingScore_AvgVal = 0, double SupporterRatingScore_AvgVal = 0,
               double minimumHostRating_val = 0)
        : Member(userNameVal, password_val, fullname_val, phonenumber_val, email_val,
                 homeadress_val, skills, creditpoint_val, HostRatingScore_AvgVal,
                 SkillRatingScore_AvgVal, SupporterRatingScore_AvgVal), minimumHostRating(minimumHostRating_val) {}
    
    //Method
    void addTimeSlot(TimeSlot* timeSlot) {
        availableTimeSlots.push_back(timeSlot);
    }

    int getNumberOfAvailableTimeSlots() {
        return availableTimeSlots.size();
    }

    void displayNumberOfAvailableTimeSlots() {
        cout << "Number of available time slots: " << getNumberOfAvailableTimeSlots() << "\n";
    }

    //Method
    double getMinimumHostRating() {
        return minimumHostRating;
    }

    void displayMinimumHostRating() {
        cout << "Minimum host rating: " << getMinimumHostRating() << "\n";
    }

};
