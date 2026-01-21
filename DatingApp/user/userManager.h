/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: userManager.h
    Description: Header file for the user manager.
*/
#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "user.h"
#include "../storage/database.h"
#include <memory>
#include <utility> // used functions: std::pair
#include <vector>

namespace User {

    /* Class description: UserManager
        EN: Manages user-related operations such as registration, login, profile updates, and others.
        PL: Zarządza operacjami związanymi z użytkownikami, takimi jak rejestracja, logowanie, aktualizacje profilu i inne.
    */
    class UserManager {
    public:
        /* Function description: UserManager Constructor
            EN: Initializes the UserManager with a reference to the database.
            PL: Inicjalizuje UserManager z referencją do bazy danych.
        */
        UserManager(Storage::Database& db);

        /* Function description: registerUser
            EN: Registers a new user in the database.
            PL: Rejestruje nowego użytkownika w bazie danych.
        */
        bool registerUser(User& user);

        /* Function description: login
            EN: Authenticates a user based on username and password.
            PL: Uwierzytelnia użytkownika na podstawie nazwy użytkownika i hasła.
        */
        bool login(const std::string& username, const std::string& password);

        /* Function description: getUserByUsername
            EN: Retrieves a user by their username.
            PL: Pobiera użytkownika na podstawie jego nazwy użytkownika.
        */
        std::unique_ptr<User> getUserByUsername(const std::string& username);

        /* Function description: updateUser
            EN: Updates the user's profile information in the database.
            PL: Aktualizuje informacje profilowe użytkownika w bazie danych.
        */
        bool updateUser(User& user);

        /* Function description: changePassword
            EN: Changes the password for a given user ID.
            PL: Zmienia hasło dla danego ID użytkownika.
        */
        bool changePassword(int userId, const std::string& newPassword);

        /* Function description: deleteAccount
            EN: Deletes a user account and associated data from the database.
            PL: Usuwa konto użytkownika oraz powiązane dane z bazy danych.
        */
        bool deleteAccount(int userId);

        /* Function description: getPotentialMatches
            EN: Retrieves a list of potential matches for the current user based on profile compatibility.
            PL: Pobiera listę potencjalnych dopasowań dla bieżącego użytkownika na podstawie zgodności profili.
        */
        std::vector<std::pair<User, int>> getPotentialMatches(const User& currentUser);
                
        /* Function description: addLike
            EN: Records a "like" from one user to another in the database.
            PL: Zapisuje "lajk" od jednego użytkownika do drugiego w bazie danych.
        */
        bool addLike(int senderId, int receiverId);

        /* Function description: checkMatch
            EN: Checks if there is a mutual "like" between two users.
            PL: Sprawdza, czy istnieje wzajemny "lajk" między dwoma użytkownikami.
        */
        bool checkMatch(int senderId, int receiverId);

        /* Function description: getLikeCount
            EN: Retrieves the number of likes received by a user.
            PL: Pobiera liczbę lajków otrzymanych przez użytkownika.
        */
        int getLikeCount(int userId);

        /* Function description: getMatches
            EN: Retrieves a list of users who have a mutual "like" with the current user.
            PL: Pobiera listę użytkowników, którzy mają wzajemny "lajk" z bieżącym użytkownikiem.
        */
        std::vector<User> getMatches(int currentUserId);

        /* Function description: addRejection
            EN: Records a "rejection" from one user to another in the database.
            PL: Zapisuje "odrzucenie" od jednego użytkownika do drugiego w bazie danych.
        */
        bool addRejection(int senderId, int receiverId);

        /* Function description: getAllUsers
            EN: Retrieves a list of all users in the database.
            PL: Pobiera listę wszystkich użytkowników w bazie danych.

            Additional info:
            -> works only in admin mode.
        */
        std::vector<User> getAllUsers();

    private:
        Storage::Database& db_;
        /* Function description: rowToUser
            EN: Converts a database row into a User object.
            PL: Konwertuje wiersz bazy danych na obiekt User.
        */
        std::unique_ptr<User> rowToUser(const std::vector<std::string>& row);
    };

}

#endif