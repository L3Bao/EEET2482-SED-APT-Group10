#include "Member.h"
#include <algorithm>  
#include "Service.h"
#include "User.h"
using namespace std;


//Constructors
Member::Member(string userId, string username, string password, string contact, string address):User(move(userId), move(username), move(password), move(contact), move(address)){
}
Member::Member(string userId, string username, string password, string contact, string address , vector<string> skills, float requiredHostRating, vector<Member*> blockedMembers, float averageHostRating, float averageSupporterRating, string city, int creditPoints):User(move(userId), move(username), move(password), move(contact), move(address)){
    this->skills = move(skills);
    this->requiredHostRating = requiredHostRating;
    this->blockedMembers = move(blockedMembers);
    this->averageHostRating = averageHostRating;
    this->averageSupporterRating = averageSupporterRating;
    this->city = move(city);
    this->creditPoints = creditPoints;
}
//Getters and Setters
vector<string> Member::getSkills(){
    return this->skills;
}
float Member::getRequiredHostRating(){
    return this->requiredHostRating;
}
vector<Member*> Member::getBlockedMembers(){
    return this->blockedMembers;
}
float Member::getAverageHostRating(){
    return this->averageHostRating;
}
float Member::getAverageSupporterRating(){
    return this->averageSupporterRating;
}
string Member::getCity(){
    return this->city;
}
int Member::getCreditPoints(){
    return this->creditPoints;
}
void Member::setSkills(vector<string> skills){
    this->skills = move(skills);
}
void Member::setRequiredHostRating(float requiredHostRating){
    this->requiredHostRating = requiredHostRating;
}
void Member::setBlockedMembers(vector<Member*> blockedMembers){
    this->blockedMembers = move(blockedMembers);
}
void Member::setAverageHostRating(float averageHostRating){
    this->averageHostRating = averageHostRating;
}
void Member::setAverageSupporterRating(float averageSupporterRating){
    this->averageSupporterRating = averageSupporterRating;
}
void Member::setCity(string city){
    this->city = move(city);
}
void Member::setCreditPoints(int creditPoints){
    this->creditPoints = creditPoints;
}
void Member::toString(){
    cout << "Member: " << endl;
    cout << "User ID: " << this->getUserId() << endl;
    cout << "Username: " << this->getUsername() << endl;
    cout << "Password: " << this->getPassword() << endl;
    cout << "Contact: " << this->getContact() << endl;
    cout << "Address: " << this->getAddress() << endl;
    cout << "Skills: " << endl;
    for (int i = 0; i < skills.size(); i++) {
        cout << skills[i] << endl;
    }
    cout << "Required Host Rating: " << this->getRequiredHostRating() << endl;
    cout << "Blocked Members: " << endl;
    for (int i = 0; i < blockedMembers.size(); i++) {
        cout << blockedMembers[i]->getUsername() << endl;
    }
    cout << "Average Host Rating: " << this->getAverageHostRating() << endl;
    cout << "Average Supporter Rating: " << this->getAverageSupporterRating() << endl;
    cout << "City: " << this->getCity() << endl;
    cout << "Credit Points: " << this->getCreditPoints() << endl;
}

//Methods
void Member::blockMember(Member* memberToBlock) {
    // Check if member is already blocked
    if (memberToBlock && find(blockedMembers.begin(), blockedMembers.end(), memberToBlock) == blockedMembers.end()) {
        blockedMembers.push_back(memberToBlock);
        cout << "Member " << memberToBlock->getUsername() << " has been blocked." << endl;
    } else {
        cout << "Invalid member or member is already blocked." << endl;
    }
}
void Member::unblockMember(Member* memberToUnblock) {
    // Check if member is already blocked
    if (memberToUnblock && find(blockedMembers.begin(), blockedMembers.end(), memberToUnblock) != blockedMembers.end()) {
        blockedMembers.erase(remove(blockedMembers.begin(), blockedMembers.end(), memberToUnblock), blockedMembers.end());
        cout << "Member " << memberToUnblock->getUsername() << " has been unblocked." << endl;
    } else {
        cout << "Invalid member or member is not blocked." << endl;
    }
}
void Member::viewRequests(vector<Service*> serviceList){
    for (int i = 0; i < serviceList.size(); i++) {
        //Check if the service is requested by the blocked member
        if (find(blockedMembers.begin(), blockedMembers.end(), serviceList[i]->offeringMember) != blockedMembers.end()) {
            continue;
        }
        //Check if the service is requested by the member
        if (serviceList[i]->offeringMember == this) {
            continue;
        }
        //Check if the service is requested by the member with a lower host rating
        if (serviceList[i]->offeringMember->getAverageHostRating() < this->getRequiredHostRating()) {
            continue;
        }
        cout << "Service ID: " << serviceList[i]->serviceID << endl;
        cout << "Service Type: " << serviceList[i]->serviceType << endl;
        cout << "Required Skills: " << endl;
        for (int j = 0; j < serviceList[i]->requiredSkills.size(); j++) {
            cout << serviceList[i]->requiredSkills[j] << endl;
        }
        cout << "Credit Cost: " << serviceList[i]->creditCost << endl;
        cout << "Duration: " << serviceList[i]->duration << endl;
        cout << "Offering Member: " << serviceList[i]->offeringMember->getUsername() << endl;
    }
}
void Member::acceptRequest(Service* service){
    if (service->offeringMember == this) {
        cout << "You cannot accept your own service." << endl;
        return;
    }
    if (service->offeringMember->getAverageHostRating() < this->getRequiredHostRating()) {
        cout << "The host rating of the offering member is lower than your required host rating." << endl;
        return;
    }
    if (service->offeringMember->getCreditPoints() < service->creditCost) {
        cout << "The offering member does not have enough credit points." << endl;
        return;
    }
    if (find(blockedMembers.begin(), blockedMembers.end(), service->offeringMember) != blockedMembers.end()) {
        cout << "The offering member has been blocked." << endl;
        return;
    }
    cout << "Service accepted." << endl;
    service->offeringMember->setCreditPoints(service->offeringMember->getCreditPoints() - service->creditCost);
    this->setCreditPoints(this->getCreditPoints() + service->creditCost);
    cout << "Credit points of " << service->offeringMember->getUsername() << ": " << service->offeringMember->getCreditPoints() << endl;
    cout << "Credit points of " << this->getUsername() << ": " << this->getCreditPoints() << endl;
    cout << "Service ID: " << service->serviceID << endl;
    cout << "Service Type: " << service->serviceType << endl;
    cout << "Required Skills: " << endl;
    for (int j = 0; j < service->requiredSkills.size(); j++) {
        cout << service->requiredSkills[j] << endl;
    }
    cout << "Credit Cost: " << service->creditCost << endl;
    cout << "Duration: " << service->duration << endl;
    cout << "Offering Member: " << service->offeringMember->getUsername() << endl;
  
}

void Member::updateSkills(){
    cout << "Enter the number of skills you want to add: ";
    int num;
    cin >> num;
    for (int i = 0; i < num; i++) {
        cout << "Skill " << i + 1 << endl;
        cout << "Enter the skill: ";
        string skill;
        cin >> skill;
        skills.push_back(skill);
    }
}

void Member::calculateAverageHostRating(vector<Rating *> ratingList){
    float sum = 0;
    int count = 0;
    //Check if there is any rating
    for (int i = 0; i < ratingList.size(); i++) {
        if (ratingList[i]->GetRatedMember() == this) {
            sum += ratingList[i]->GetHostRating();
            count++;
        }
    }
    if (count == 0) {
        averageHostRating = 0;
        cout << "No rating yet." << endl;
    } else {
        averageHostRating = sum / count;
        cout << "Average host rating: " << averageHostRating << endl;
    }
}
void Member::calculateAverageSupporterRating(vector<Rating *> ratingList){
    float sum = 0;
    int count = 0;
    //Check if there is any rating
    for (int i = 0; i < ratingList.size(); i++) {
        if (ratingList[i]->GetRatedMember() == this) {
            sum += ratingList[i]->GetSupporterRating();
            count++;
        }
    }
    if (count == 0) {
        averageSupporterRating = 0;
        cout << "No rating yet." << endl;
    } else {
        averageSupporterRating = sum / count;
        cout << "Average supporter rating: " << averageSupporterRating << endl;
    }
}
