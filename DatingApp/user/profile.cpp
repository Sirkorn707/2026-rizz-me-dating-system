/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: profile.cpp
    Description: Implementation file for the user profile.
*/
#include "Profile.h"
#include <sstream> // Used functions: std::stringstream

namespace User {

    Profile::Profile() 
        : age_(0), description_(""), gender_(Gender::Other) {
    }

    Profile::Profile(int age, std::string desc, Gender gender, std::vector<std::string> interests)
        : age_(age), description_(desc), gender_(gender), interests_(interests) {
    }

    void Profile::setAge(int newAge) {
        age_ = newAge;
    }

    void Profile::setDescription(const std::string& desc) {
        description_ = desc;
    }

    void Profile::addInterest(const std::string& interest) {
        interests_.push_back(interest);
    }

    std::string Profile::toString() const {
        std::stringstream ss;
        ss << "Wiek: " << age_ << ", Opis: " << description_ << ", Zainteresowania: ";
        for (const auto& i : interests_) {
            ss << i << " ";
        }
        return ss.str();
    }

}