#include "MemberDatabase.h"
//Methods
//Save one member to file
void MemberDatabase::saveMember (Member member){
    ofstream memberFile;
    memberFile.open("MemberDatabase.txt", ios::app);
    memberFile << member.getUserId() << endl;
    memberFile << member.getUsername() << endl;
    memberFile << member.getPassword() << endl;
    memberFile << member.getContact() << endl;
    memberFile << member.getAddress() << endl;
    memberFile << member.getSkills().size() << endl;
    for (int i = 0; i < member.getSkills().size(); i++){
        memberFile << member.getSkills()[i] << endl;
    }
    memberFile << member.getRequiredHostRating() << endl;
    memberFile << member.getBlockedMembers().size() << endl;
    for (int i = 0; i < member.getBlockedMembers().size(); i++){
        memberFile << member.getBlockedMembers()[i]->getUserId() << endl;
    }
    memberFile << member.getAverageHostRating() << endl;
    memberFile << member.getAverageSupporterRating() << endl;
    memberFile << member.getCity() << endl;
    memberFile << member.getCreditPoints() << endl;
    memberFile.close();
}
//Load all members from file
void MemberDatabase::loadMember (vector<Member> &memberList){
    ifstream memberFile;
    //if file does not exist, create it
    memberFile.open("MemberDatabase.txt");
 if (!memberFile.is_open()) {
    ofstream newMemberFile("MemberDatabase.txt");
    newMemberFile.close();
    memberFile.open("MemberDatabase.txt");
}

    string userId;
    string username;
    string password;
    string contact;
    string address;
    int skillsSize;
    vector<string> skills;
    float requiredHostRating;
    int blockedMembersSize;
    vector<Member*> blockedMembers;
    float averageHostRating;
    float averageSupporterRating;
    string city;
    int creditPoints;
    while (getline(memberFile, userId)){
        getline(memberFile, username);
        getline(memberFile, password);
        getline(memberFile, contact);
        getline(memberFile, address);
        memberFile >> skillsSize;
        memberFile.ignore();
        for (int i = 0; i < skillsSize; i++){
            string skill;
            getline(memberFile, skill);
            skills.push_back(skill);
        }
        memberFile >> requiredHostRating;
        memberFile.ignore();
        memberFile >> blockedMembersSize;
        memberFile.ignore();
        for (int i = 0; i < blockedMembersSize; i++){
            string blockedMemberId;
            getline(memberFile, blockedMemberId);
            Member* blockedMember = findMember(memberList, blockedMemberId);
            blockedMembers.push_back(blockedMember);
        }
        memberFile >> averageHostRating;
        memberFile.ignore();
        memberFile >> averageSupporterRating;
        memberFile.ignore();
        getline(memberFile, city);
        memberFile >> creditPoints;
        memberFile.ignore();
        Member member(userId, username, password, contact, address, skills, requiredHostRating, blockedMembers, averageHostRating, averageSupporterRating, city, creditPoints);
        memberList.push_back(member);
        skills.clear();
        blockedMembers.clear();
    }
    memberFile.close();
}
Member* MemberDatabase::findMember (vector<Member> memberList, string userId){
    for (int i = 0; i < memberList.size(); i++){
        if (memberList[i].getUserId() == userId){
            return &memberList[i];
        }
    }
    return NULL;
}
vector<Member*> MemberDatabase::getMemberList(){
    return this->memberList;
}

