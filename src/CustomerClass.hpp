//============================================================================
//
// Name : Marty Grefiel
// Student #: 301572130
// Student userid (email): mga137 (mga137@sfu.ca)
//
//============================================================================
// Project name:    Produce Market
// Date:            12/11/2023 
//
//
// Resources:  cplusplus.com, cppreference.com, and stackoverflow.com
//
// File:         CustomerClass.cpp
// Description:  member function definitions for customer management
//
//============================================================================

#define FMT_HEADER_ONLY
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <fmt/format.h>
#include <filesystem>

#include "CustomerClass.hpp"
#include "FreeFunctions.hpp"

void Customer::showCustomerInfo() const {
    std::cout << "Full name: " << m_customer.fullName << std::endl;
    std::cout << "Street: " << m_customer.street << std::endl;
    std::cout << "City: " << m_customer.city << std::endl;
    std::cout << "Postal Code: " << m_customer.postalCode << std::endl;
}

bool Customer::checkMembership() const {
    return m_customer.isMember;
}

void Customer::signUp()
{
    while (true) {
        std::cout << std::endl << std::endl;
        std::cout << "Enter the following information:" << std::endl;
        std::cout << "Full name: ";
        std::getline(std::cin, m_customer.fullName);
        std::cout << "Street: ";
        std::getline(std::cin, m_customer.street);
        std::cout << "City: ";
        std::getline(std::cin, m_customer.city);
        std::cout << "Postal Code: ";
        std::getline(std::cin, m_customer.postalCode);
        std::cout << std::endl << std::endl;
        

        char c;
        askForInput<char>(c, "Is the information above correct? (y/n): ");

        if (c == 'y' || c == 'Y') {
            m_customersDatabase.push_back(m_customer);
            saveCustomersDatabase();
            std::cout << std::endl;
            m_customer.isMember = true;
            break; 
        }
    }
}
// helper function for case insensitive string comparison
bool Customer::caseInsStringCmp(const std::string &s1, const std::string &s2) {
    if ((s1.size() == s2.size()) && 
            std::equal(s1.begin(), s1.end(), s2.begin(), predInsStringCmp)) {
        return true;
    }
    return false;
}

void Customer::login() {
    std::string fullName;

    std::cout << "Enter your full name: ";
    std::getline(std::cin, fullName);

    for (const customerInfo &customer : m_customersDatabase) {
        if (caseInsStringCmp(fullName, customer.fullName)) {
            size_t firstNameLocation = fullName.find_first_of(" ");
            // update: (FIXED!)
            fullName = fullName.substr(0, firstNameLocation);  // extracts the first name
            // capitalize first letter of name in case it's a lowercase
            for (size_t index{0}; const char &c : fullName) {
                if (index == 0) {
                    fullName.at(0) = std::toupper(c);
                } else { fullName.at(index) = std::tolower(c);}
                index++;
            }
            std::cout << fmt::format("Hello! Welcome, {}!", fullName) << std::endl;
            m_customer.isMember = true;
            break;
        }
    }
    if (!m_customer.isMember) {
        std::cout << std::endl;
        std::cout << "Sorry, your name is not in our database" << std::endl; 
        char choice;
        askForInput(choice, "Become a member for discount? (y/n): ");

        if (choice == 'y' || choice == 'Y') {
            signUp();
        }
    }
}
void Customer::viewCustomersDatabase() const {
    for (const customerInfo &customer : m_customersDatabase) {
        std::cout << fmt::format("{:<13}{:^4}{:<25}\n", "Full Name:", "", customer.fullName);
        std::cout << fmt::format("{:<13}{:^4}{:<25}\n", "Street:", "", customer.street);
        std::cout << fmt::format("{:<13}{:^4}{:<25}\n", "City:", "", customer.city);
        std::cout << fmt::format("{:<13}{:^4}{:<25}\n", "Postal Code:", "", customer.postalCode);
        std::cout << std::endl;
    }
}
bool Customer::loadCustomersDatabase() {
    if (std::ifstream inputFile{m_fileName, std::ios::in}) {
        // std::cout << "file opened successfully\n";
        std::string stringRead;
        size_t firstCharName, lastCharname;

        std::filesystem::path fileNamePath{m_fileName};

        if (std::filesystem::is_empty(fileNamePath)) {
            std::cout << fmt::format("No customer data to load. File {} empty\n", m_fileName);
            return false;
        }

        while(!inputFile.eof()) {
            for (size_t lineNumber{1}; lineNumber <= 4; lineNumber++) {
                std::getline(inputFile, stringRead);
                // skips the line in the beginning of the file if there's one
                if (stringRead == "") {
                    lineNumber--;
                    continue;
                }
                firstCharName = stringRead.find_first_of("\"");
                lastCharname = stringRead.find_last_of("\"") - 1;
                switch (lineNumber) {
                    case 1: 
                        m_customer.fullName = stringRead.substr(firstCharName+1, lastCharname-firstCharName); break;
                    case 2:
                        m_customer.street = stringRead.substr(firstCharName+1, lastCharname-firstCharName); break;
                        break;
                    case 3:
                        m_customer.city = stringRead.substr(firstCharName+1, lastCharname-firstCharName); break;
                        break;
                    case 4:
                        m_customer.postalCode = stringRead.substr(firstCharName+1, lastCharname-firstCharName); break;
                        break;
                }
            }
            // gets rid of the blank lines to properly read data in the file
            std::getline(inputFile, stringRead);  
            m_customersDatabase.push_back(m_customer);
        }
        // commented this line below since destructor of stream object closes the file
        // when stream object goes out of scope
        // inputFile.close(); 
    }
    else {
        std::cout << "File could not be found. File does not exist";
        std::cout << std::endl;
        return false;  // when no such file exist
    }
    return true;  // when file is successfully loaded
}
//  save customer's data 
bool Customer::saveCustomersDatabase() {
    if (std::ofstream outputFile{m_fileName, std::ios::out | std::ios::app}) {
        outputFile << fmt::format("\n{:<13}{:^4}{:<25}\n", "Full Name:", "", "\"" + m_customer.fullName + "\"");
        outputFile << fmt::format("{:<13}{:^4}{:<25}\n", "Street:", "", "\"" + m_customer.street +"\"");
        outputFile << fmt::format("{:<13}{:^4}{:<25}\n", "City:", "", "\"" + m_customer.city + "\"");
        outputFile << fmt::format("{:<13}{:^4}{:<25}\n", "Postal Code:", "", "\"" + m_customer.postalCode + "\"");

        // commented this line below since destructor of stream object closes the file
        // when stream object goes out of scope
        // outputFile.close();
        // }
        std::cout << std::endl << "Successfully saved customer(s) data" << std::endl;
    }
    else { 
        std::cout << "Failed to save customer(s) data" <<std::endl;
        return false;
    }
    return true;  // returns true if customer(s) data successfully saved
}
