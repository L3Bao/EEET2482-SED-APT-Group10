// Member.h
#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
private:
    std::string name; // Member's name
    int id;           // Member's ID

public:
    Member(const std::string& name, int id) : name(name), id(id) {}

    // Setters and getters
    void SetName(const std::string& newName) { name = newName; }
    std::string GetName() const { return name; }

    void SetId(int newId) { id = newId; }
    int GetId() const { return id; }
};

#endif // MEMBER_H