#include "service.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <sstream>

using std::cin, std::cout;
int Service::serviceCount = 0;

void UpdateLine(std::string& line, int fieldIndex, const std::string& newValue) {
    std::stringstream linestream(line);
    std::string segment;
    std::vector<std::string> segments;

    // Split the line into segments
    while (getline(linestream, segment, ',')) {
        segments.push_back(segment);
    }

    // Update the specified field
    if (fieldIndex < segments.size()) {
        segments[fieldIndex] = newValue;
    }

    // Reconstruct the line
    std::ostringstream newLine;
    for (size_t i = 0; i < segments.size(); ++i) {
        newLine << segments[i];
        if (i < segments.size() - 1) newLine << ",";
    }
    line = newLine.str();
}


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
    std::cout << "Enter the Service ID you want to update (e.g., s-1): ";
    std::cin >> serviceID;  // Get the Service ID to update

    std::cout << "What would you like to update?\n";
    std::cout << "1. Service Type\n";
    std::cout << "2. Required Skills\n";
    std::cout << "3. Credit Cost\n";
    std::cout << "4. Duration\n";
    std::cout << "Enter your choice (1-4): ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string filename = "service.txt";
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    bool serviceFound = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream linestream(line);
            std::string currentID;
            getline(linestream, currentID, ',');

            if (currentID == serviceID) {
                serviceFound = true;

                // Depending on the user's choice, update different attributes
                switch (choice) {
                    case 1: {
                        std::cout << "Enter new service type: ";
                        std::getline(std::cin, serviceType);
                        UpdateLine(line, 1, serviceType);  // Update the service type in the line
                        break;
                    }
                    case 2: {
                        std::cout << "Enter required skills (separated by semicolons): ";
                        std::string skills;
                        std::getline(std::cin, skills);
                        UpdateLine(line, 2, skills);  // Update the required skills in the line
                        break;
                    }
                    case 3: {
                        std::cout << "Enter new credit cost: ";
                        std::string cost;
                        std::getline(std::cin, cost);
                        UpdateLine(line, 3, cost);  // Update the credit cost in the line
                        break;
                    }
                    case 4: {
                        std::cout << "Enter new duration: ";
                        std::string duration;
                        std::getline(std::cin, duration);
                        UpdateLine(line, 4, duration);  // Update the duration in the line
                        break;
                    }
                    default:
                        std::cout << "Invalid choice.\n";
                        return;
                }
            }
            lines.push_back(line);  // Store the line for later rewriting
        }
        file.close();
    } else {
        std::cerr << "Unable to open file " << filename << "\n";
        return;
    }
    if (serviceFound) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (size_t i = 0; i < lines.size(); ++i) {
                outFile << lines[i];
                // Write a newline if this isn't the last line
                if (i < lines.size() - 1) {
                outFile << '\n';
                }
            }
            outFile.close();
            std::cout << "Service updated successfully.\n";
        } else {
            std::cerr << "Unable to open file " << filename << " for writing.\n";
        }
    } else {
        std::cout << "Service with ID " << serviceID << " not found.\n";
    }
}

void Service::DeleteService() {
    std::string inputID;
    std::cout << "Enter the Service ID you want to delete (e.g., s-1): ";
    std::cin >> inputID;

    std::string filename = "service.txt";
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    bool serviceFound = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream linestream(line);
            std::string currentID;
            getline(linestream, currentID, ',');

            if (currentID != inputID) {
                // If the current line's ID doesn't match the input ID, keep it
                lines.push_back(line);
            } else {
                // Mark that we found and will delete the service
                serviceFound = true;
            }
        }
        file.close();  // Close the file after reading all lines

        if (serviceFound) {
            // Open the same file in write mode (this will overwrite the existing file)
            std::ofstream outFile(filename);
            if (outFile.is_open()) {
                for (size_t i = 0; i < lines.size(); ++i) {
                    outFile << lines[i];
                    // Write a newline if this isn't the last line
                    if (i < lines.size() - 1) {
                        outFile << '\n';
                    }
                }
                outFile.close();
                std::cout << "Service with ID " << inputID << " has been deleted successfully.\n";
            } else {
                std::cerr << "Unable to open file " << filename << " for writing.\n";
            }
        } else {
            std::cout << "Service with ID " << inputID << " not found.\n";
        }
    } else {
        std::cerr << "Unable to open file " << filename << "\n";
    }
}


int main() {
    InitializeServiceCount();

    Service service;
    service.DeleteService();

    return 0;
}