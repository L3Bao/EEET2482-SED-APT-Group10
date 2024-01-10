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

    

};


#endif