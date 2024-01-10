#include "SkillRent.h"

SkillRent::SkillRent(DateTime *from, DateTime *to, Skill *rentedSkill) {
    this->rentFrom = from;
    this->rentTo = to;
    this->rentedSkill = rentedSkill;
}