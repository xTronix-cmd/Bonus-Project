#pragma once 
#include <iostream>
#include <string>
#include <map>
#include <ios>
#include <fstream>
#include <fmt/format.h>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <array>

#include "CustomerClass.hpp"
#include "ProduceClass.hpp"
// #include "FreeFunctions.hpp"

#define BACKSPACE 8
#define ENTER 13

// typedef std::vector<std::string> VSA;
typedef std::map<std::string, std::string> MSS;
struct managerInfo {
    std::string m_name;
    MSS loginInfo;
};

class Manager : public Customer, public ProduceByAmount, public ProduceByWeight {
    private:

    inline static managerInfo m_managerInfo;

    public:

    managerInfo getManagerInfo() const;
    void setManagerInfo(const std::string &name, const std::string &username, const std::string &password);

    // process password input
    std::string inputPassword();
    bool managerLogin();
    // change existing user password
    void changePassword();
    void saveManagerInfo(const std::string &filename);
    void loadManagerInfo(const std::string &filename);
    void viewManagerInfo();
    void addMember(Customer &customer);
    bool deleteMember(const std::string &name);
    void removeItems(ProduceByAmount &amount, ProduceByWeight &weight, const std::string &itemToDel);
    const std::array<std::string, 3> processAddItems(const std::string &command);
};
