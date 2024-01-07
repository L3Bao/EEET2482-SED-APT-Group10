#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>

class Member;

class Service {
private:
    std::string serviceID;
    std::vector<std::string> requiredSkills;
    double creditCost;
    std::string duration;
    Member* offeringMember;

    static int serviceCount;
    static bool initialized;

    static bool InitializeServiceCount();
public:
    Service(const std::string& id = "", const std::vector<std::string>& skills = {}, double cost = 0.0, const std::string& time = "1h", Member* member = nullptr);

    ~Service();

    void CreateService(const std::string& id, const std::vector<std::string>& skills, double cost, const std::string& time);
    void ViewService(const std::string& id);
    void UpdateService(const std::string& id, int choice, const std::string& newValue);
    void DeleteService(const std::string& id);

    static std::string GenerateServiceId();
    friend void UpdateLine();
};

#endif