// Admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>

class User;

class Admin : public User {
public:
    Admin();

    bool login(std::string username, std::string pass) override;
    void resetUserPassword(const std::string &userId, const std::string &newPassword);
    bool isAdmin() const;

    // Override the saveUser method to save to admins.txt.
    void saveUser() override;
};

#endif // ADMIN_H   
