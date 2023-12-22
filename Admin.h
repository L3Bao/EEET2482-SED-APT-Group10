// Admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"  // Including the User class

class Admin : public User {  // Inheriting from User
public:
    // Using the User class's constructor
    using User::User;

    // Function to verify if the user is an admin, always returns true for Admin instances
    bool isAdmin() const;

    // Function to reset a user's password
    void resetPassword(const std::string& userId, const std::string& newPassword);
};

#endif // ADMIN_H
