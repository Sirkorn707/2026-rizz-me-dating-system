/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: profile.h
    Description: Header file for the user profile.
*/
#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <vector>
#include <iostream>

namespace User {

    /* Class description: Gender (enum)
        EN: Enum representing user gender.
        PL: Enum reprezentujący płeć użytkownika.

        Additional info:
        -> enum class used here to provide strong typing and avoid name clashes.
        -> only one of three values can be assigned to a Profile Gender.
    */
    enum class Gender {
        Male = 0,
        Female = 1,
        Other = 2
    };

    /* Class description: Profile
        EN: Class representing a user profile.
        PL: Klasa reprezentująca profil użytkownika.
    */
    class Profile {
    public:
        /* Function description: Profile() constructors
            EN: Constructors for Profile class.
            PL: Konstruktory klasy Profile.
        */
        Profile();
        Profile(int age, std::string desc, Gender gender, std::vector<std::string> interests);

        /* Function description: Profile getters
            EN: Getters for Profile class attributes.
            PL: Gettery dla atrybutów klasy Profile.
        */
        int getAge() const { return age_; }
        std::string getDescription() const { return description_; }
        Gender getGender() const { return gender_; }
        std::vector<std::string> getInterests() const { return interests_; }

        /* Function description: Profile setters
            EN: Setters for Profile class attributes.
            PL: Settery dla atrybutów klasy Profile.
        */
        void setAge(int newAge);
        void setDescription(const std::string& desc);
        void addInterest(const std::string& interest);

        /* Function description: Profile toString()
            EN: Returns a string representation of the Profile.
            PL: Zwraca reprezentację tekstową profilu.
        */
        std::string toString() const;

        /* Function description: Profile setInterestsVector()
            EN: Sets the interests vector.
            PL: Ustawia wektor zainteresowań.
        */
        void setInterestsVector(const std::vector<std::string>& newInterests) {
            interests_ = newInterests;
        }
    private:
        int age_;
        std::string description_;
        Gender gender_;
        std::vector<std::string> interests_;
    };

}

#endif