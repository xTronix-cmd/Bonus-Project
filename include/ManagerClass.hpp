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

#include "CustomerClass.hpp"
// #include "FreeFunctions.hpp"
#include "ProduceClass.hpp"

#define BACKSPACE 8
#define ENTER 13

// typedef std::vector<std::string> VSA;
typedef std::map<std::string, std::string> MSS;
struct managerInfo {
    std::string m_name;
    MSS loginInfo;
};

class Manager : public Customer, public Produce {
    private:

    inline static managerInfo m_managerInfo;
    managerInfo m2_managerInfo;

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

    bool deleteMember(const std::string &name) {
        std::string firstName;
        for (auto itCustomerInfo{m_customersDatabase.begin()}; itCustomerInfo != m_customersDatabase.begin();) {
            size_t firstNameLocation = itCustomerInfo->fullName.find_first_of(" ");
            firstName = itCustomerInfo->fullName.substr(0, firstNameLocation);
            if (caseInsStringCmp(name, firstName)) {
                m_customersDatabase.erase(itCustomerInfo);
                return true;
            }
            itCustomerInfo++;
        }
    }
    // void addItemWeight(ProduceByWeight &weight, std::string itemToAdd, double price) {
    //     m_isManager = true;
    //     weight.addItem(itemToAdd, price);
    // }

    // void addItemAmount(ProduceByAmount &amount, std::string itemToAdd, double price) {
    //     m_isManager = true;
    //     amount.addItem(itemToAdd, price);

    // }
    // void removeItemAmount(ProduceByAmount &amount, std::string itemToDel) {
    //     m_isManager = true;
    //     amount.removeItem(itemToDel);
    // }
    // void removeItemWeight(ProduceByWeight &weight, std::string itemToDel) {
    //     m_isManager = true;
    //     weight.removeItem(itemToDel);
    // }
};
