#pragma once
#define FMT_HEADER_ONLY
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <fmt/format.h>
#include <filesystem>

#include "FreeFunctions.hpp"
class Customer {
    protected:
        struct customerInfo {
            std::string fullName{};
            std::string street{};
            std::string city{};
            std::string postalCode{};
            int customerNumber{};  // implement this later!
            bool isMember{false};

        } m_customer;

        bool isManager{false};
        inline static std::vector<customerInfo> m_customersDatabase;
        inline static const char m_fileName[] = "./data/CustomersDatabase.txt";
    
    public:
        Customer() {
            // load the existing database in file when an object is instantiated
        }
        virtual ~Customer() = default;  // just incase if we later inherit from this class
        void showCustomerInfo() const;

        int checkMembership();

        void signUp();

        std::vector<customerInfo> getCustomerDatabase() const;

        void login();
        void viewCustomersDatabase() const;
        bool loadCustomersDatabase();
        bool saveCustomersDatabase();
        //  save customer's data 
        bool saveCurrentCustomer();
};