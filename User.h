// User.h
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

class User {
protected:
    std::string userId, name, password, contact, address;
    bool isLoggedIn;

public:
    User();
    static std::string generateUserId();
    std::vector<std::string> split(const std::string &s, char delimiter);
    bool login(std::string username, std::string pass);
    void saveUser();
    void createNewUser(std::string name, std::string password, std::string contact, std::string address);
    void updateUser(std::string newName = "", std::string newPassword = "", std::string newContact = "", std::string newAddress = "");
    void deleteSpecificUser(const std::string &delUserId);
    void deleteUser();
    void updateAllUsers();
    bool isUserLoggedIn();
    void displayUserDetails();
    void logout();
};

#endif // USER_H
