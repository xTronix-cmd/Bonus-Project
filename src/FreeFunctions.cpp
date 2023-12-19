#include "FreeFunctions.hpp"

bool caseInsStringCmp(const std::string &s1, const std::string &s2) {
    if ((s1.size() == s2.size()) && 
            std::equal(s1.begin(), s1.end(), s2.begin(), predInsStringCmp)) {
        return true;
    }
    return false;
}