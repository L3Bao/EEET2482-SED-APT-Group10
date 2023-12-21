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
using std::endl;
using std::vector;
using std::string;
using std::getline;

//Global Variables

//Role of User
bool Guest_choice, Member_choice, Admin_choice = false;
bool ExitProgram = false;
bool isLog = true;

//Bool Data
bool payAble = false;
bool Exit = false;

//Class of Skill
class Skill
{
    private:
        string location = "NULL";
        vector<string> skills = {};
        string available = "NULL";
        string start_period = "NULL";
        string end_period = "NULL";
    
        //Record Data for Host   
        string username = "NULL";
        string fullname = "NULL";
        string phoneNumber = "NULL";

    //Method
    public: 
        House(){}
        
    friend class Member;
    friend class System;
    friend class Admin;
};

//Class of Member
class Member
{
    private:
        string userName = "NULL";
        string password = "NULL";
        string fullName = "NULL";
        string phoneNumber = "NULL";
        string email = "NULL";
        string HomeAddress = "NULL";
        vector<string> skills = {};
        string comment = "NULL"; //comment on how one's performance
        int creditPoint = 20; //20 credit when creating Member 
        double HiringCreditPoint  = 0;
        double HostRatingScore_Avg = 0;
        double SkillRatingScore_Avg = 0;
        double SupporterRatingScore_Avg = 0;
        double minimum_HostRatingScore_Avg = 0;
        
        //Recored Data
        Member* OccupyMem; //only 1
        vector<Skill*> supporter_skills; // one can have many skills
        Skill* supporter_occupy; //Constraint a supporter can only perform a skill at a time

        vector<Member*> listOfrequests;
        vector<Member*> listOfreviews;


        //This attribute for update database
        Skill SkillData;

    //Method
    public:
        Member(){}

        bool LogIn();

        void ShowInfo()
        {
            cout << "\nYour Information:\n";
            cout << "   Fullname = " << fullName << ". Username = " << userName << ". Password = " << password << "\n"
                 << "   Phone number = " << phoneNumber << ".   Home Adress = " << HomeAddress << ".   Email = " << email << "\n"
                 << "   Credit point = " << creditPoint << ".   Host Rating Score = " << HostRatingScore_Avg << ".\n";

                 
            cout << "\nYour Skill Information:\n";
            cout << "   Supporter location = " << supporter_skills->location << ". Supporter skills = " << supporter_skills-> skills << ".\n"
                 << "   Skill Rating Score = " << SkillRatingScore_Avg << ". Availability = " << supporter_skills->available << ".\n"
                 << "   Require credit point for hiring = " << HiringCreditPoint << ".  Minimum require occupier rating = " << minimum_HostRatingScore_Avg << ".\n"
                 << "   Start Period = "<< supporter_skills->start_period << ". End Period = " << supporter_skills->end_period << ".\n";

            if(supporter_occupy->username != "NULL" )
            {
                cout << "\nYour Supporter has been Occupied:\n";
                cout << "   Supporter's location = " << supporter_occupy->location << ". Skills description = " << supporter_occupy->skills << ". ";

                for(auto each : Database)
                {
                    if(each->userName == supporter_occupy->username)
                    {
                       cout << "Supporter Rating Score = " << each->SupporterRatingScore_Avg;
                    }
                }
                cout << ". Supporter start period = " << supporter_occupy->start_period << ". Supporter end period = " << supporter_occupy->end_period << "\n"
                << "   Information of Owner of this skill: \n"
                << "        >Fullname = " << supporter_occupy->fullname << ". Phone number = " << supporter_occupy->phoneNumber << ". Username = " << supporter_occupy->username << "\n";
            }
            

        }

        //Show List of Request
        void ShowListRequest()
        {
            bool check = false;
            int cnt = 1;
            if(listOfrequests.empty() != 1){
                cout << "\nYour list of requests:\n";
                for(auto each : listOfrequests)
                {
                    cout << cnt << ") Username = " << each->userName << ". Phone number = " << each->phoneNumber << ". Occupied Rating Score = " << each->occupierRatingScore_Avg << ".\n";
                    cnt++;
                }
            }


            if(listOfrequests.empty() != 1)
            {
                string input_index;
                cout << "\nChoose the member you want to occupy your skill please enter the INDEX NUMBER: ";
                cin >> input_index;
                int i = 0;
                for(auto each : Database)
                {
                    if(each->userName == userName)
                    {
                        for(auto request : each->listOfrequests)
                        {
                            if(true)
                                i++;
                            if(input_index == std::to_string(i))
                            {
                                string requestName = request->userName;
                                for(auto data : Database)
                                {
                                    if(data->userName == requestName)
                                    {
                                        if(data->supporter_skills->username != "NULL" && data->creditPoint >= HiringCreditPoint && data->HostRatingScore_Avg >= minimum_HostRatingScore_Avg)
                                        {
                                            OccupyMem = request;

                                            each->OccupyMem = request;
                                            data->supporter_occupy = supporter_skills;

                                            each->creditPoint = each->creditPoint + HiringCreditPoint;
                                            request->creditPoint = request->creditPoint - HiringCreditPoint;

                                            each->supporter_skills->available = "Unavailable";

                                            //delete the request
                                            for(auto loop : Database)
                                            {
                                                int i = 0;
                                                if(loop->userName != userName){
                                                    for(auto list : loop->listOfrequests)
                                                    {
                                                        if(list->userName == requestName)
                                                        {
                                                            loop->listOfrequests.erase(loop->listOfrequests.begin() + i);
                                                        }
                                                        i++;
                                                    }
                                                }
                                                else
                                                    loop->listOfrequests.clear();
                                                    
                        
                                            }
                                            cout << "Successfully accept the request!\n";
                                            check = true;
                                            break;

                                        }
                                        else
                                        {
                                            cout << "Syntax Error!!\n";
                                            break;
                                        }
                                    }
                                }
                                if(check == false)
                                {
                                    cout << "The condition of the requester didn't match!\n";
                                    break;
                                }
                            }
        
                        }
                    }

                } 
            }
            else
                cout << "\nThere are none request!\n";
        }

        //Feature 5 List House can be occupied
        void ListSkillsToBeBooked()
        {
            string choice;
            string Input_start_period;
            string Input_end_period;
            string choice2, choice3;

            string RentingStr;
            double Input_HiringcreditPoint;
            double Input_MinimumHostRatingScore_Avg;
            bool loop = true;
            
            if(OccupyMem->userName == "NULL"){
                cout << "Do you want to list your skills available to be booked (Y/N): ";
                cin >> choice;
                if (choice == "Y") {
                    supporter_skills->available = "Available";
                    cout << "Set the credit point to hire this skill: ";
                    cin >> Input_HiringcreditPoint;
                    HiringCreditPoint = Input_HiringcreditPoint;
                    for(auto each : Database)
                    {
                        if(each->userName == userName)
                            each->HiringCreditPoint = Input_HiringcreditPoint;
                    }
                    cout << "Set the minimum required occupier rating to hire this supporter skill: ";
                    cin >> Input_MinimumHostRatingScore_Avg;
                    minimum_HostRatingScore_Avg = Input_MinimumHostRatingScore_Avg;
                    for(auto each : Database)
                    {
                        if(each->userName == userName)
                            each->minimum_occupierRatingScore_Avg = Input_MinimumHostRatingScore_Avg;
                    }

                    cout << "Set start period for skill availability (dd/mm/yyyy): ";
                    cin >> Input_start_period;
                    supporter_skills->start_period = Input_start_period;

                    cout << "Set end period for skill availability (dd/mm/yyyy): ";
                    cin >> Input_end_period;
                    supporter_skills->end_period = Input_end_period;
                
                } else if (choice == "N") {
                    supporter_skills->available = "Unavailable";
                } else {
                    cout << "Syntax error\n";
                }
            }
            else
            {
                cout << "\nAlready has member occupied!\n";
            }
            
        }

        //Show House available for rent
        void showskillsAvailable()
        {
            int cnt = 1; //Number order
            string tempUsername;
            string choice;
            for(auto each : Database)
            {

                if((each->supporter_skills)->available == "Available" & each->userName != userName)
                {
                    cout <<"\n" << cnt <<  ") Supporter: " << each->fullName << ". Location at " << (each->supporter_skills)->location << ".\n"
                         << "Description: " << (each->supporter_skills)->skills << ". Supporter Rating Score =  " << each->SupporterRatingScore_Avg << 
                         ". Require credit point for hiring = " << each->HiringCreditPoint << ". Minimum require host rating = " << each->minimum_HostRatingScore_Avg 
                         << ". Start period = " << (each->supporter_skills)->start_period << ". End period = " << (each->supporter_skills)->end_period << ".\n"
                         "For more contact call " << each->phoneNumber << ". Email: " << each->email << ". Home address: " << each->HomeAddress << ".\n\n";
                        
                    tempUsername = each->userName;
                    for(auto each : Database)
                    {
                        if(tempUsername == each->userName)
                        {
                            int cnt = 1;
                            for(auto reviews : each->listOfreviews)
                            {
                                cout <<"    > Feedback " <<cnt << ". " << reviews->userName << ": " << reviews->comment << ". supporter rating Score = " << reviews->SupporterRatingScore_Avg << "\n";
                                cnt++;
                            }
                        }
                    }
                    cnt++;
                }
            }
            cout << "Do you want to hire a person of this skill (Y/N)?: ";
            cin >> choice;
            if(choice == "Y") 
            {
                string input_index;
                string alreadyRequest;
                bool check = true;
                cout << "\nChoosing the skill to send the request to the supporter (please enter INDEX NUMBER): ";
                cin >> input_index;
                int index = 0;
           
                for(auto each : Database){
                    for(auto request : each->listOfrequests)
                    {
                        if(request->userName == userName)
                        {
                            check = false;
                        }

                    }
                    if((each->supporter_skills)->available == "Available" && each->userName != userName)
                    {
                        index++;
                    } 
                    if(check == false && input_index == std::to_string(index))  
                    {
                        cout << "You already requested this skill!\n";
                        break;
                    }  
                    if(check == true && input_index == std::to_string(index))
                    {
                        if(creditPoint >= each->HiringCreditPoint && HostRatingScore_Avg >= each->minimum_HostRatingScore_Avg && supporter_occupy->username == "NULL")
                        {
                            each->listOfrequests.push_back(this);
                            cout << "Successfully request this house!\n";
                            break;
                        }
                        else
                        {
                            if(!(creditPoint >= each->HiringCreditPoint))
                                cout << "Sorry your credit point is not enough to occupy this skill!\n";
                            if(!(HostRatingScore_Avg >= each->minimum_HostRatingScore_Avg))
                                cout << "Sorry your host Rating Score is not enough to request this skill!\n";
                            if(!(supporter_occupy->username == "NULL"))
                                cout << "Sorry you already occupied a skill!\n";
                            break;
                        }

                    }
                    check = true;
 
                }
            }
            else
                cout << "Exiting to main menu\n";

    
        }

        void showslistofReview();

        //Gain access
        friend class System;
        friend class Admin;
     
};

//class of Admin
class Admin
{
    private:

    public:
        string admin_userName;
        string admin_password;
        Admin(){}
        Admin(string admin_userName, string admin_password){
            this->admin_userName = admin_userName;
            this->admin_password = admin_password;
        }
        void ShowDatabase()
        {
            //Show List of data of Members 
            int cnt = 1; // order number
            cout << "\n";
            for(auto each: Database)
            {
                cout << cnt << ") Member's name: " << each->fullName << ". Username: " << each->userName << ". Phone number: " << each->phoneNumber
                     << ". Credit point: " << each->creditPoint << ". Occupier score: " << each->HostRatingScore_Avg  << ". Supporter Rating score: " << each->SupporterRatingScore_Avg 
                     << ". House location: " << (each->supporter_skills)->location << ". Description: " << (each->supporter_skills)->skills << ". Availability: " << (each->supporter_skills)->available 
                     << ". Require credit point for occupy = " << each->HiringCreditPoint << ".  Minimum require occupier rating = " << each->minimum_HostRatingScore_Avg 
                     << ". Start period = " << (each->supporter_skills)->start_period << ". End period = " << (each->supporter_skills)->end_period << ". "
                     << "\n";
                cnt++;
                if(each->listOfreviews.empty() != 1)
                {
                    int i = 1;
                    for(auto review : each->listOfreviews)
                    {
                        cout << "   >" << i << ") " << review->userName << ": " << review->comment << ". House Rating Score = " << review->SupporterRatingScore_Avg << ".\n";
                        i++;
                    }
                    i = 0;
                    cout << "\n";
                
                }
                else
                {
                    cout << "There is no reviews for this house!\n\n";
                }
            }


        }
        void Admin_Login(Admin* temp);
    friend class System;    
};