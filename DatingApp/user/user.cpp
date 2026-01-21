/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: user.cpp
    Description: Implementation file for the user class.
*/
#include "user.h"
#include <iostream>

namespace User {

    User::User(int id, const std::string& username, const std::string& passwordHash, const Profile& profile)
        : id_(id), username_(username), passwordHash_(passwordHash), profile_(profile) {
    }

    User::User(int id, std::string username, std::string passwordHash)
        : id_(id), username_(username), passwordHash_(passwordHash) {
    }

    int User::getId() const { return id_; }
    std::string User::getUsername() const { return username_; }
    std::string User::getPasswordHash() const { return passwordHash_; }
    int User::getAge() const { return age_; }

    void User::setId(int newId) {
        id_ = newId;
    }

    void User::setAge(int newAge) {
        if (newAge >= 18 && newAge < 120) {
            age_ = newAge;
        } else {
            std::cerr << "[SYSTEM] Nieprawidłowy wiek. " << newAge << ". Ustawiono 18." << std::endl;
            age_ = 18; 
        }
    }

    void User::setPasswordHash(const std::string& newHash) {
        if (!newHash.empty()) {
            passwordHash_ = newHash;
        }
    }

    Profile& User::getProfile() {
        return profile_;
    }

    const Profile& User::getProfile() const {
        return profile_;
    }

    std::ostream& operator<<(std::ostream& os, const User& user) {
        os << "ID: " << user.id_ << " | " << user.username_ << " (" << user.age_ << " lat)\n";
        os << user.profile_.toString(); 
        return os;
    }

}