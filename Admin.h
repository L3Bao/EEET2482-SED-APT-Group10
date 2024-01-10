// Admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>

class User;

class Admin : public User {
public:
    Admin(std::string username, std::string password);

    friend class System;
};

#endif // ADMIN_H   
