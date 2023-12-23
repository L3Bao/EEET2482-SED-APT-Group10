#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>

class Member;

class Service {
private:
    std::string serviceID;
    std::string serviceType;
    std::vector<std::string> requiredSkills;
    double creditCost;
    std::string duration;
    Member* offeringMember;

    static int serviceCount;
public:
    Service(const std::string& type = "", const std::vector<std::string>& skills = {}, double cost = 0.0, const std::string& time = "1h", Member* member = nullptr);

    ~Service();

    void CreateService();
    void ViewService();
    void UpdateService();
    void DeleteService();

    static std::string GenerateServiceId();
    friend void InitializeServiceCount();
};

#endif