#ifndef MEMBERDATABASE_H
#define MEMBERDATABASE_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Member.h"
using namespace std;

class MemberDatabase
{
private:
    vector<Member*> memberList;
    fstream memberFile;
public:
    MemberDatabase();
    ~MemberDatabase();
    void saveMember(Member member);
    void loadMember(vector<Member> &memberList);
    Member* findMember(vector<Member> memberList, string userId);
    vector<Member*> getMemberList();
};
#endif
