/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: user.h
    Description: Header file for the user class.
*/
#ifndef USER_H
#define USER_H

#include "profile.h"

#include <string>
#include <iostream>

namespace User {

    /* Class description: User
        EN: Class representing a user in the dating application.
        PL: Klasa reprezentująca użytkownika w aplikacji randkowej.
    */
    class User {
    public:
        /* Function description: User()
            EN: Constructors for User class.
            PL: Konstruktory klasy User.
        */
        User(int id, const std::string& username, const std::string& passwordHash, const Profile& profile);
        User(int id, std::string username, std::string passwordHash);

        /* Function description: User getters
            EN: Getters for User class attributes.
            PL: Gettery dla atrybutów klasy User.
        */
        int getId() const;
        std::string getUsername() const;
        std::string getPasswordHash() const;
        int getAge() const;

        /* Function description: User setters
            EN: Setters for User class attributes.
            PL: Settery dla atrybutów klasy User.
        */
        void setId(int newId);
        void setAge(int newAge); 
        void setPasswordHash(const std::string& newHash);

        /* Function description: User Profile access
            EN: Access to the user's profile.
            PL: Dostęp do profilu użytkownika.

            NOTE: one version is READ-ONLY (const), the other allows modifications.
        */
        Profile& getProfile();
        const Profile& getProfile() const;

        /* Function description: User operator<<()
            EN: Overloads the output stream operator for User.
            PL: Przeciążenie operatora strumienia wyjściowego dla klasy User.
        */
        friend std::ostream& operator<<(std::ostream& os, const User& user);

    private:
        int id_;
        std::string username_;
        std::string passwordHash_;
        int age_;
        Profile profile_;
    };

}

#endif