#ifndef INPUTCHECK_H
#define INPUTCHECK_H

#include <iostream>

class System;

class InputCheck {
public:
    bool passwordCheck(std::string password);

    bool usernameCheck(std::string username, System *system);

    bool nameCheck(std::string name);

    bool emailCheck(std::string email, System *system);

    bool phoneNumCheck(std::string phoneNum, System *system);

    bool addressCheck(std::string address);

    bool time(std::string time);

    bool timeRange(std::string startTime, std::string endTime);

    friend class System;
};


#endif