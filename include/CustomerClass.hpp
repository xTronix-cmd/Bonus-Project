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

        inline static std::vector<customerInfo> m_customersDatabase;
        inline static const char m_fileName[] = "./data/CustomersDatabase.txt";
    
    public:
        Customer() {
            loadCustomersDatabase();
            // load the existing database in file when an object is instantiated
        }
        virtual ~Customer() = default;  // just incase if we later inherit from this class
        void showCustomerInfo() const;

        bool checkMembership() const;

        void signUp();
        // helper functions for case insensitive string comparison
        inline static bool predInsStringCmp(const char &a, const char &b) {
            return (std::tolower(a) == std::tolower(b));
        }

        bool caseInsStringCmp(const std::string &s1, const std::string &s2);

        void login();
        void viewCustomersDatabase() const;
        bool loadCustomersDatabase();
        //  save customer's data 
        bool saveCustomersDatabase();
};