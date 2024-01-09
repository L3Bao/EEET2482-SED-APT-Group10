// User.cpp
#include "User.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

User::User(std::string username, std::string password) {
    this->username = std::move(username);
    this->password = std::move(password);
}