#ifndef SKILLRENT_H
#define SKILLRENT_H

class DateTime;
class Skill;

class SkillRent {
    DateTime* rentFrom;
    DateTime* rentTo;
    Skill* rentedSkill;

public:
    SkillRent(DateTime* from, DateTime* to, Skill* skill);

    friend class System;

    friend class Member;
};

#endif