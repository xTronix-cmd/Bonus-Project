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
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  cplusplus.com, cppreference.com, and stackoverflow.com
//
// File:    FreeFunctions.hpp
// Descriptions: Helper functions and messages for prompting user
//
//============================================================================

#pragma once
#define FMT_HEADER_ONLY
#include <iostream>
#include <fmt/format.h>

template <typename T>
void askForInput(T &c, const std::string &prompt) {
    while (true) {
        std::cout << prompt;
        std::cin >> c;

        if (std::cin.fail()) {  // checks to see if there's any error when trying to extract from input stream
            std::cin.clear();  // clears the bit to good bit 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush the bad input from the stream
            std::cout << "Invalid input. Try again.\n";
            continue; 
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush out any remaining bad input
        // this check to see if we flush more than one character
        // which indicates a possibility of not extracting the input properly
        if (std::cin.gcount() > 1) {
            std::cout << "Invalid input. Try again.\n";
            continue;
        }
        break;
    }
    std::cout << std::endl;
}
template <typename T>
void askForInput(T &a, T &b, const std::string prompt) {
    while (true) {
        std::cout << prompt;
        std::cin >> a >> b;

        if (std::cin.fail()) {  // checks to see if there's any error when trying to extract from input stream
            std::cin.clear();  // clears the bit to good bit 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush the bad input from the stream
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush out any remaining bad input
        // this check to see if we flush more than one character
        // which indicates a possibility of not extracting the input properly
        if (std::cin.gcount() > 1) {
            continue;
        }
        break;
    }
}
// helper functions for case insensitive string comparison
inline static bool predInsStringCmp(const char &a, const char &b) {
    return (std::tolower(a) == std::tolower(b));
}
bool caseInsStringCmp(const std::string &s1, const std::string &s2);

enum membershipFlag { MEMBER = 1, MANAGER };