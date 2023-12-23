#include "service.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <sstream>

using std::cin, std::cout;
int Service::serviceCount = 0;

void InitializeServiceCount() {
    std::string filename = "service.txt";
    std::ifstream file(filename);
    std::string line;
    int maxId = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream linestream(line);
            std::string serviceId;
            std::getline(linestream, serviceId, ','); // Assuming Service ID is the first entry

            // Extract the numeric part of the Service ID (e.g., "s-15" -> 15)
            if (!serviceId.empty() && serviceId[0] == 's' && serviceId[1] == '-') {
                int idNum = std::stoi(serviceId.substr(2));
                maxId = std::max(maxId, idNum);
            }
        }
        Service::serviceCount = maxId; // Set the static counter to the highest found ID
        file.close();
    }
}

Service::Service(const std::string& type, const std::vector<std::string>& skills, double cost, const std::string& time, Member* member) {
    serviceID = Service::GenerateServiceId();
    serviceType = type;
    requiredSkills = skills;
    creditCost = cost;
    duration = time;
    offeringMember = member;
}

Service::~Service() {}

std::string Service::GenerateServiceId() {
    return "s-" + std::to_string(++serviceCount);
}

void Service::CreateService() {
    std::cout << "Service ID generated: " << serviceID << '\n';
    // Clear input buffer before taking multiple words
    std::cout << "Enter service type: ";
    std::getline(std::cin, serviceType);

    std::cout << "Enter required skills (type '-1' to finish, '-2' to remove the last skill): ";
    std::string skill;

    while (true) {
        std::getline(std::cin, skill);

        // Check for the sentinel value to end the loop
        if (skill == "-1") {
            if (requiredSkills.empty()) {
                std::cout << "You must enter at least one skill. Please continue entering skills: ";
            } else {
                break; // Exit the loop if the user types '-1'
            }
        }
        // Allow the user to delete the last entered skill
        else if (skill == "-2") {
            if (!requiredSkills.empty()) {
                requiredSkills.pop_back();
                std::cout << "Last skill removed. Continue entering skills: ";
            } else {
                std::cout << "No skills to remove. Continue entering skills: ";
            }
        } else if (skill.empty()) {
            std::cout << "Skill cannot be empty. Please enter a valid skill: ";
        }
        // Add the skill to the list
        else {
            requiredSkills.push_back(skill);
            std::cout << "Skill added. Continue entering skills: ";
        }
    }

    std::cout << "Enter credit cost: ";
    std::cin >> creditCost;
    std::cout << "Enter duration: ";
    std::cin >> duration;

    // Define the file name
    std::string filename = "service.txt";

    // Check if the file already exists
    std::ifstream infile(filename);
    bool fileExists = infile.good();

    // Open a file in append mode.
    std::ofstream file(filename, std::ios::app | std::ios::ate); // Open file in append mode and move to the end of the file
    long file_length = file.tellp();  // Get the current position, which is the file's length

    if (file.is_open()) {
        if (!fileExists || file_length == 0) {
            // If the file was just created or is empty, write headers
            file << "Service ID,Service Type,Required Skills,Credit Cost,Duration\n";
        }

        if (file_length > 0) {
            // If the file is not empty, prepend a newline character to the new entry
            file << '\n';
        }

        // Write details to the file in CSV format.
        file << serviceID << ',';
        file << serviceType << ',';
        
        // Combine all skills into a single semicolon-separated string
        for (size_t i = 0; i < requiredSkills.size(); ++i) {
            file << requiredSkills[i];
            if (i < requiredSkills.size() - 1) file << ";";  // Separate skills with a semicolon
        }
        file << ',';  // End of the skills section
        
        file << creditCost << ',';
        file << duration;  // Do not add a newline character here

        std::cout << "Service has been successfully created and saved to " << filename << "\n";
        file.close();  // Close the file after writing
    } else {
        std::cerr << "Unable to open file\n";
    }
}

void Service::ViewService() {
    std::string inputID;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Enter the Service ID you want to view (e.g., s-1), or type 'exit' to stop: ";
        std::cin >> inputID;

        // Allow the user to exit the loop
        if (inputID == "exit") {
            break;
        }

        // Input validation
        if (inputID.empty() || inputID.find("s-") == std::string::npos) {
            std::cout << "Invalid input. Please enter a valid Service ID (e.g., s-1).\n";
            continue;  // Skip the rest of the loop and prompt again
        }

        std::string filename = "service.txt";
        std::ifstream file(filename);
        std::string line;

        // File open error
        if (!file.is_open()) {
            std::cerr << "Unable to open file " << filename << ". Please check if the file exists and you have the necessary permissions.\n";
            continue;  // Skip the rest of the loop and prompt again
        }

        bool serviceFound = false;
        while (getline(file, line)) {
            std::stringstream linestream(line);
            std::string currentID, currentType, currentSkills, currentCost, currentDuration;

            getline(linestream, currentID, ',');
            getline(linestream, currentType, ',');
            getline(linestream, currentSkills, ',');
            getline(linestream, currentCost, ',');
            getline(linestream, currentDuration);

            // Format error
            if (linestream.fail() || currentID.empty()) {
                std::cerr << "There was a problem reading the file. Please check the file format.\n";
                break;
            }

            if (currentID == inputID) {
                std::cout << "Service ID: " << currentID << '\n';
                std::cout << "Service type: " << currentType << '\n';
                std::cout << "Required skills: " << currentSkills << '\n';
                std::cout << "Credit cost: " << currentCost << '\n';
                std::cout << "Duration: " << currentDuration << '\n';
                serviceFound = true;
                validInput = true;  // Indicate that a valid input was provided
                break;  // Stop searching as the service has been found
            }
        }

        file.close();

        if (!serviceFound && validInput) {
            std::cout << "Service with ID " << inputID << " not found. Please try again.\n";
        }
    }
}

void Service::UpdateService() {
    std::cout << "Enter service ID: ";
    std::cin >> serviceID;
    std::cout << "Enter service type: ";
    std::cin >> serviceType;
    std::cout << "Enter required skills (separated by spaces): ";
    std::string skill;
    while (std::cin >> skill) {
        requiredSkills.push_back(skill);
    }
    std::cout << "Enter credit cost: ";
    std::cin >> creditCost;
    std::cout << "Enter duration: ";
    std::cin >> duration;
}

void Service::DeleteService() {
    serviceID = "";
    serviceType = "";
    requiredSkills.clear();
    creditCost = 0.0;
    duration = "";
    offeringMember = nullptr;
}

int main() {
    InitializeServiceCount();

    Service service;
    service.ViewService();

    return 0;
}