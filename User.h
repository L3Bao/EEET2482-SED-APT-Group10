// User.h
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

class User {
protected:
    std::string username;
    std::string password;

public:
    User(std::string username, std::string password);
    friend class System;
};

#endif // USER_H
