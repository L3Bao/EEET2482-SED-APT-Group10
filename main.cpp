#include "Admin.h"
#include <iostream>
#include <string>

void userMenu(User* currentUser);
void adminMenu(Admin* admin);  // Notice the parameter is a User pointer.

int main() {
    User* currentUser = nullptr;
    std::string input, username, password;

    while (true) {
        std::cout << "\nLogin System" << std::endl;
        std::cout << "1. Login as User" << std::endl;
        std::cout << "2. Login as Admin" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);
        int choice = std::stoi(input);

        if (choice == 3) {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        std::cout << "Enter username: ";
        std::getline(std::cin, username);
        std::cout << "Enter password: ";
        std::getline(std::cin, password);

        switch (choice) {
            case 1:
                currentUser = new User();
                if (currentUser->login(username, password)) {
                    std::cout << "User login successful!" << std::endl;
                    userMenu(currentUser);
                } else {
                    std::cout << "User login failed." << std::endl;
                }
                break;
            case 2:
                currentUser = new Admin();
                if (currentUser->login(username, password)) {
                    std::cout << "Admin login successful!" << std::endl;
                    adminMenu(dynamic_cast<Admin*>(currentUser));  // Dynamically cast to Admin*
                } else {
                    std::cout << "Admin login failed." << std::endl;
                }
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                continue;
        }
        delete currentUser; // Clean up
        currentUser = nullptr;
    }
    return 0;
}


void userMenu(User* currentUser) {
    currentUser->displayUserDetails();
}

void adminMenu(Admin* admin) {
    if (admin == nullptr) {
        std::cout << "Error: No admin user provided." << std::endl;
        return;
    }

    std::string input, userId, newPassword;
    int choice;

    while (true) {
        std::cout << "\nAdmin Menu:" << std::endl;
        std::cout << "1. Reset User Password" << std::endl;
        std::cout << "2. Exit Admin Menu" << std::endl;
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);
        try {
            choice = std::stoi(input);
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid input, please enter a number." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "Enter the user ID of the account to reset the password: ";
                std::getline(std::cin, userId);
                std::cout << "Enter the new password: ";
                std::getline(std::cin, newPassword);
                admin->resetUserPassword(userId, newPassword);
                std::cout << "Password reset successfully for user ID " << userId << "." << std::endl;
                break;
            case 2:
                std::cout << "Exiting admin menu." << std::endl;
                return;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    }
}

