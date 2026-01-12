/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: passwordManager.h
    Description: Header file for the password manager class.
*/
#ifndef SECURITY_PASSWORDMANAGER_H
#define SECURITY_PASSWORDMANAGER_H

#include <string>
#include <functional> // Used functions: std::hash

namespace Security {

    /* Class description: PasswordManager
        EN: Class responsible for password hashing and management.
        PL: Klasa odpowiedzialna za hashowanie i zarządzanie hasłami użytkowników.
    */
    class PasswordManager {
    public:
        /* Function description: hashPassword()
            EN: Static method to hash a password using std::hash.
            PL: Metoda statyczna haszująca hasło przy użyciu std::hash.

            Additional info:
                -> This is a simple hashing method for demonstration purposes.
                -> std::hash is not cryptographically secure. For production, using a stronger hashing algorithm is better.
                -> It is impossible to reverse the hash to get the original password.
                -> More info: https://en.cppreference.com/w/cpp/utility/hash.
        */
        static std::string hashPassword(const std::string& password) {
            std::hash<std::string> hasher;
            size_t hashValue = hasher(password);
            return std::to_string(hashValue);
        }
    };

}

#endif