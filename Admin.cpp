// Admin.cpp
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Confirming this user is an admin
bool Admin::isAdmin() const {
    return true;  // This instance is inherently an admin, so always returns true
}

// Function to reset a user's password
void Admin::resetPassword(const std::string& userId, const std::string& newPassword) {
    // This assumes the existence of user data in a file and that each User object can access and modify its own password.
    // Read all users, find the matching userId, and update the password
    std::vector<std::string> lines;
    std::string line;
    std::ifstream file("users.txt");
    bool found = false;

    while (getline(file, line)) {
        std::vector<std::string> details = split(line, ',');
        if (details.size() >= 5 && details[0] == userId) {
            details[2] = newPassword;  // Assuming the password is the third element
            line = details[0] + "," + details[1] + "," + details[2] + "," + details[3] + "," + details[4];
            found = true;
        }
        lines.push_back(line);
    }
    file.close();

    if (found) {
        // Rewrite the file with the updated information
        std::ofstream outFile("users.txt", std::ios::trunc);
        for (const auto &l : lines) {
            outFile << l << std::endl;
        }
        std::cout << "Password for user ID: " << userId << " has been reset." << std::endl;
    } else {
        std::cout << "User ID not found." << std::endl;
    }
}
