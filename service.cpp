#include "service.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <sstream>

using std::cin, std::cout;
int Service::serviceCount = 0;
bool Service::initialized = Service::InitializeServiceCount();

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


bool Service::InitializeServiceCount() {
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
    return true;
}

Service::Service(const std::string& id, const std::string& type, const std::vector<std::string>& skills, double cost, const std::string& time, Member* member) {
    serviceID = id;
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

void Service::CreateService(const std::string& id, const std::string& type, const std::vector<std::string>& skills, double cost, const std::string& time) {
    serviceID = id;
    serviceType = type;
    requiredSkills = skills;
    creditCost = cost;
    duration = time;

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

void Service::ViewService(const std::string& id) {
    std::string filename = "service.txt";
    std::ifstream file(filename);
    std::string line;
    bool serviceFound = false;


    // File open error
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << ". Please check if the file exists and you have the necessary permissions.\n";
    } else {
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

            if (currentID == id) {
                std::cout << "Service ID: " << currentID << '\n';
                std::cout << "Service type: " << currentType << '\n';
                std::cout << "Required skills: " << currentSkills << '\n';
                std::cout << "Credit cost: " << currentCost << '\n';
                std::cout << "Duration: " << currentDuration << "h" << '\n';
                serviceFound = true;
                break;  // Stop searching as the service has been found
            }
        }

        file.close();

        if (!serviceFound) {
            std::cout << "Service with ID " << id << " not found. Please try again.\n";
        }
    }
    
}

void Service::UpdateService(const std::string& id, int choice, const std::string& newValue) {
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

            if (currentID == id) {
                serviceFound = true;
                // Update the line based on the choice
                UpdateLine(line, choice, newValue);
            }
            lines.push_back(line);  // Store the line for later rewriting
        }
        file.close();
    } else {
        std::cerr << "Unable to open file " << filename << "\n";
        return;
    }

    // Rewrite the file with updated content
    if (serviceFound) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (size_t i = 0; i < lines.size(); ++i) {
                outFile << lines[i];
                if (i < lines.size() - 1) {
                    outFile << '\n';  // Write a newline if this isn't the last line
                }
            }
            outFile.close();
            std::cout << "Service updated successfully.\n";
        } else {
            std::cerr << "Unable to open file " << filename << " for writing.\n";
        }
    } else {
        std::cout << "Service with ID " << id << " not found.\n";
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
    Service service;  // Assuming default constructor is appropriate
    int choice = 0;

    while (true) {
        std::cout << "\nService Management System\n";
        std::cout << "1. Create Service\n";
        std::cout << "2. View Service\n";
        std::cout << "3. Update Service\n";
        std::cout << "4. Delete Service\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear the input buffer to handle any extraneous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string id = Service::GenerateServiceId();
                std::string type, skill, time;
                double cost;
                std::vector<std::string> skills;

                std::cout << "Service ID generated: " << id << '\n';
                std::cout << "Enter service type: ";
                std::getline(std::cin, type);

                std::cout << "Enter required skills (type '-1' to finish, '-2' to remove the last skill): ";

                while (true) {
                    std::getline(std::cin, skill);

                    // Check for the sentinel value to end the loop
                    if (skill == "-1") {
                        if (skills.empty()) {
                            std::cout << "You must enter at least one skill. Please continue entering skills: ";
                        } else {
                            break; // Exit the loop if the user types '-1'
                        }
                    }
                    // Allow the user to delete the last entered skill
                    else if (skill == "-2") {
                        if (!skills.empty()) {
                            skills.pop_back();
                            std::cout << "Last skill removed. Continue entering skills: ";
                        } else {
                            std::cout << "No skills to remove. Continue entering skills: ";
                        }
                    } else if (skill.empty()) {
                        std::cout << "Skill cannot be empty. Please enter a valid skill: ";
                    }
                    // Add the skill to the list
                    else {
                        skills.push_back(skill);
                        std::cout << "Skill added. Continue entering skills: ";
                    }
                }

                std::cout << "Enter credit cost: ";
                std::cin >> cost;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter duration: ";
                std::getline(std::cin, time);

                service.CreateService(id, type, skills, cost, time);
                break;
            }
            case 2: {
                std::string inputID;
                std::cout << "Enter the Service ID you want to view (e.g., s-1): ";
                std::cin >> inputID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer

                // Input validation
                if (inputID.empty() || inputID.find("s-") == std::string::npos) {
                    std::cout << "Invalid input. Please enter a valid Service ID (e.g., s-1).\n";
                } else {
                    service.ViewService(inputID);
                }
                break;
            }
            case 3: {
                std::string serviceID;
                std::cout << "Enter the Service ID you want to update (e.g., s-1): ";
                std::cin >> serviceID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                int choice;
                std::string newValue;
                bool isValidInput = false;  // Flag to track if the input is valid

                std::cout << "What would you like to update?\n";
                std::cout << "1. Service Type\n";
                std::cout << "2. Required Skills\n";
                std::cout << "3. Credit Cost\n";
                std::cout << "4. Duration\n";
                std::cout << "Enter your choice (1-4): ";
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                while (!isValidInput) {
                    if (choice == 1) {
                        std::cout << "Enter new service type: ";
                        std::getline(std::cin, newValue);
                        isValidInput = !newValue.empty();  // Validate that input is not empty
                    } else if (choice == 2) {
                        std::cout << "Enter required skills (separated by semicolons): ";
                        std::getline(std::cin, newValue);
                        // Validate that input is not empty and correctly formatted
                        isValidInput = !newValue.empty() && newValue.find_first_not_of(" ;abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
                    } else if (choice == 3) {
                        std::cout << "Enter new credit cost: ";
                        std::getline(std::cin, newValue);
                        // Validate that the cost is a number and is positive
                        try {
                            double cost = std::stod(newValue);
                            isValidInput = cost > 0;
                        } catch (const std::exception& e) {
                            isValidInput = false;
                        }
                    } else if (choice == 4) {
                        std::cout << "Enter new duration (in hours, e.g., 1.5 for one and a half hours): ";
                        std::getline(std::cin, newValue);
                        // Validate that the duration is a number and is positive
                        try {
                            double duration = std::stod(newValue);
                            isValidInput = duration > 0;
                        } catch (const std::exception& e) {
                            isValidInput = false;
                        }
                    } else {
                        std::cout << "Invalid choice.\n";
                        break;
                    }

                    if (!isValidInput) {
                        std::cout << "Invalid input. Please try again.\n";
                    }
                }

                if (isValidInput) {
                    service.UpdateService(serviceID, choice, newValue);
                }
                break;
            }
  
            case 4:
                service.DeleteService();
                break;
            case 5:
                std::cout << "Exiting the Service Management System.\n";
                return 0;  // Exit the program
            default:
                std::cout << "Invalid choice, please try again.\n";
        }

        // Pause and wait for user acknowledgment before returning to the main menu
        std::cout << "\nPress Enter to return to the main menu...";
        std::cin.get();  // Wait for user to press Enter
    }

    return 0;
}