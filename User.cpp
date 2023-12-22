// User.cpp
#include "User.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

User::User() : isLoggedIn(false) {
    // Constructor is currently empty. Customize as needed.
}

std::string User::generateUserId() {
    std::ifstream file("users.txt");
    std::string line, lastId;
    int idNum = 1;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string segment;
        std::getline(iss, segment, ',');
        if (!segment.empty()) {
            lastId = segment;
        }
    }
    file.close();

    if (!lastId.empty() && lastId[0] == 'u') {
        idNum = std::stoi(lastId.substr(1)) + 1;
    }

    std::stringstream newIdStream;
    newIdStream << "u" << std::setw(2) << std::setfill('0') << idNum;
    return newIdStream.str();
}

std::vector<std::string> User::split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool User::login(std::string username, std::string pass) {
    std::ifstream file("users.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> userDetails = split(line, ',');
        if (userDetails.size() < 5) continue;

        if (userDetails[1] == username && userDetails[2] == pass) {
            userId = userDetails[0];
            name = userDetails[1];
            password = userDetails[2];
            contact = userDetails[3];
            address = userDetails[4];
            isLoggedIn = true;
            return true;
        }
    }
    return false;
}

void User::saveUser() {
    if (!name.empty() && !password.empty()) {
        std::ofstream file("users.txt", std::ios::app);
        file << userId << "," << name << "," << password << "," << contact << "," << address << std::endl;
        file.close();
    }
}

void User::createNewUser(std::string name, std::string password, std::string contact, std::string address) {
    this->name = name;
    this->password = password;
    this->contact = contact;
    this->address = address;
    this->userId = generateUserId();
    saveUser();
}

void User::updateUser(std::string newName, std::string newPassword, std::string newContact, std::string newAddress) {
    if (isLoggedIn) {
        if (!newName.empty()) name = newName;
        if (!newPassword.empty()) password = newPassword;
        if (!newContact.empty()) contact = newContact;
        if (!newAddress.empty()) address = newAddress;

        updateAllUsers();
        std::cout << "User updated successfully!" << std::endl;
    } else {
        std::cout << "No user is logged in to update." << std::endl;
    }
}

void User::deleteSpecificUser(const std::string &delUserId) {
    std::vector<std::string> lines;
    std::string line;
    std::ifstream file("users.txt");
    while (getline(file, line)) {
        if (line.substr(0, line.find(',')) != delUserId) {
            lines.push_back(line);
        }
    }
    file.close();

    std::ofstream outFile("users.txt", std::ios::trunc);
    for (const auto &l : lines) {
        outFile << l << std::endl;
    }
}

void User::deleteUser() {
    if (isLoggedIn) {
        std::string idToDelete = userId;
        logout();
        deleteSpecificUser(idToDelete);
        std::cout << "User deleted successfully!" << std::endl;
    } else {
        std::cout << "No user is logged in to delete." << std::endl;
    }
}

void User::updateAllUsers() {
    std::vector<std::string> lines;
    std::string line;
    std::ifstream file("users.txt");
    while (getline(file, line)) {
        std::vector<std::string> details = split(line, ',');
        if (details.size() >= 5 && details[0] == userId) {
            line = userId + "," + name + "," + password + "," + contact + "," + address;
        }
        lines.push_back(line);
    }
    file.close();

    std::ofstream outFile("users.txt", std::ios::trunc);
    for (const auto &l : lines) {
        outFile << l << std::endl;
    }
}

bool User::isUserLoggedIn() {
    return isLoggedIn;
}

void User::displayUserDetails() {
    if (isLoggedIn) {
        std::cout << "User ID: " << userId << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Contact: " << contact << std::endl;
        std::cout << "Address: " << address << std::endl;
    } else {
        std::cout << "No user is logged in." << std::endl;
    }
}

void User::logout() {
    isLoggedIn = false;
    userId = "";
    name = "";
    password = "";
    contact = "";
    address = "";
}
