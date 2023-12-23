// Admin.cpp
#include "Admin.h"
#include <fstream>
#include <sstream>
#include <vector>

Admin::Admin() : User()
{
    // Customize as needed. Perhaps set isAdminFlag to true.
}

bool Admin::login(std::string username, std::string pass)
{
    std::ifstream file("admins.txt");
    if (!file.is_open())
    {
        std::cout << "Failed to open admins.txt" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> userDetails = split(line, ',');
        if (userDetails.size() < 5)
        {
            std::cout << "Skipping malformed line." << std::endl;
            continue;
        }

        std::cout << "Checking user: " << userDetails[1] << std::endl; // Debug print

        if (userDetails[1] == username && userDetails[2] == pass)
        {
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

void Admin::saveUser()
{
    if (!name.empty() && !password.empty())
    {
        std::ofstream file("admins.txt", std::ios::app);
        file << userId << "," << name << "," << password << "," << contact << "," << address << std::endl;
        file.close();
    }
}

void Admin::resetUserPassword(const std::string &userId, const std::string &newPassword)
{
    std::vector<std::string> lines;
    std::string line;
    std::ifstream file("users.txt");
    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> userDetails = split(line, ',');
        if (userDetails.size() >= 5 && userDetails[0] == userId)
        {
            // Update password for the found user.
            userDetails[2] = newPassword;
            line = userDetails[0] + "," + userDetails[1] + "," + newPassword + "," + userDetails[3] + "," + userDetails[4];
        }
        lines.push_back(line);
    }
    file.close();

    // Write updated information back to file.
    std::ofstream outFile("users.txt", std::ios::trunc);
    for (const auto &l : lines)
    {
        outFile << l << std::endl;
    }
}

bool Admin::isAdmin() const
{
    // As before, or possibly just return true if this is always an admin.
    return true;
}
