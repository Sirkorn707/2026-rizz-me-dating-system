/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: userManager.cpp
    Description: Implementation file for the user manager.
*/
#include "userManager.h"
#include <iostream>
#include <string>
#include <algorithm> // Used functions: std::find, std::sort
#include "../utils/helperFunctions.h"
#include "../matching/matchAlgorithm.h"

namespace User {

    UserManager::UserManager(Storage::Database& db) : db_(db) {
    }

    bool UserManager::registerUser(User& user) {
        std::string name = user.getUsername();
        std::string hash = user.getPasswordHash();
        int age = user.getProfile().getAge();

        std::string desc = user.getProfile().getDescription();
        int gender = (int)user.getProfile().getGender();

        std::string interestsStr = "";
        const auto& vec = user.getProfile().getInterests();
        for (size_t i = 0; i < vec.size(); ++i) {
            interestsStr += vec[i];
            if (i < vec.size() - 1) {
                interestsStr += ",";
            }
        }

        std::string sql = "INSERT INTO USERS (USERNAME, PASSWORD_HASH, AGE, DESCRIPTION, GENDER, INTERESTS) VALUES ('" 
                          + name + "', '" 
                          + hash + "', " 
                          + std::to_string(age) + ", '" 
                          + desc + "', " 
                          + std::to_string(gender) + ", '" 
                          + interestsStr + "');";

        if (db_.execute(sql)) {
            return true;
        } else {
            std::cerr << "[SYSTEM ERROR] Nie udało się dodać użytkownika." << std::endl;
            return false;
        }
    }
    
    bool UserManager::login(const std::string& username, const std::string& password) {
        auto userPtr = getUserByUsername(username);

        if (userPtr == nullptr) {
            return false;
        }

        if (userPtr->getPasswordHash() == password) {
            return true;
        }

        return false;
    }

    std::unique_ptr<User> UserManager::getUserByUsername(const std::string& username) {
        std::string sql = "SELECT * FROM USERS WHERE USERNAME = '" + username + "';";
        auto results = db_.query(sql);
        if (results.empty()) return nullptr;
        
        return rowToUser(results[0]);
    }

    std::unique_ptr<User> UserManager::rowToUser(const std::vector<std::string>& row) {
        try {
            int id = std::stoi(row[0]);
            std::string name = row[1];
            std::string hash = row[2];
            int age = std::stoi(row[3]);

            std::string description = "";
            Gender gender = Gender::Other;
            std::vector<std::string> interestsVec;

            if (row.size() > 4) {
                description = row[4];
            }
            
            if (row.size() > 5) {
                std::string genderStr = row[5];
                if (!genderStr.empty() && genderStr != "NULL") {
                    try {
                        int g = std::stoi(genderStr);
                        gender = static_cast<Gender>(g);
                    } catch(...) {}
                }
            }

            if (row.size() > 6) {
                std::string interestsStr = row[6];
                if (!interestsStr.empty() && interestsStr != "NULL") {
                    interestsVec = Utils::HelperFunctions::splitString(interestsStr, ',');
                }
            }

            Profile tempProfile(age, description, gender, interestsVec);

            auto user = std::make_unique<User>(id, name, hash, tempProfile);
            return user;
        } catch (...) {
            return nullptr;
        }
    }

    bool UserManager::updateUser(User& user) {
        std::string desc = user.getProfile().getDescription();
        int gender = static_cast<int>(user.getProfile().getGender());

        std::string interests = Utils::HelperFunctions::joinVector(user.getProfile().getInterests(), ',');

        std::string sql = "UPDATE USERS SET "
                        "DESCRIPTION = '" + desc + "', "
                        "GENDER = " + std::to_string(gender) + ", "
                        "INTERESTS = '" + interests + "' "
                        "WHERE ID = " + std::to_string(user.getId()) + ";";

        if (db_.execute(sql)) {
            std::cout << "[SYSTEM] Profil zaktualizowany w bazie." << std::endl;
            return true;
        } else {
            std::cerr << "[SYSTEM] Błąd aktualizacji profilu." << std::endl;
            return false;
        }
    }

    bool UserManager::changePassword(int userId, const std::string& newPassword) {
        std::string sql = "UPDATE USERS SET PASSWORD_HASH = '" + newPassword + "' WHERE ID = " + std::to_string(userId) + ";";
        
        if (db_.execute(sql)) {
            std::cout << "[SYSTEM] Hasło zmienione pomyślnie." << std::endl;
            return true;
        } else {
            std::cerr << "[SYSTEM] Błąd zmiany hasła." << std::endl;
            return false;
        }
    }

    bool UserManager::deleteAccount(int userId) {
        std::string idStr = std::to_string(userId);
        
        db_.execute("DELETE FROM LIKES WHERE SENDER_ID=" + idStr + " OR RECEIVER_ID=" + idStr + ";");        
        db_.execute("DELETE FROM REJECTIONS WHERE SENDER_ID=" + idStr + " OR RECEIVER_ID=" + idStr + ";");        
        db_.execute("DELETE FROM MESSAGES WHERE SENDER_ID=" + idStr + " OR RECEIVER_ID=" + idStr + ";");
        std::string sql = "DELETE FROM USERS WHERE ID = " + idStr + ";";
        
        if (db_.execute(sql)) {
            std::cout << "[SYSTEM] Konto (ID: " << userId << ") zostało usunięte." << std::endl;
            return true;
        } else {
            std::cerr << "[SYSTEM] Błąd usuwania konta." << std::endl;
            return false;
        }
    }

    std::vector<std::pair<User, int>> UserManager::getPotentialMatches(const User& currentUser) {
            std::vector<std::pair<User, int>> candidates;
            
            Gender myGender = currentUser.getProfile().getGender();

            std::string sql = "SELECT * FROM USERS WHERE ID != " + std::to_string(currentUser.getId()) + 
                      " AND ID NOT IN (SELECT RECEIVER_ID FROM LIKES WHERE SENDER_ID=" + std::to_string(currentUser.getId()) + ")" +
                      " AND ID NOT IN (SELECT RECEIVER_ID FROM REJECTIONS WHERE SENDER_ID=" + std::to_string(currentUser.getId()) + ");";
            auto results = db_.query(sql);

            for (const auto& row : results) {
                auto candidatePtr = rowToUser(row);
                if (!candidatePtr) continue;

                Gender candidateGender = candidatePtr->getProfile().getGender();

                if (myGender == Gender::Male && candidateGender != Gender::Female) continue; 
                if (myGender == Gender::Female && candidateGender != Gender::Male) continue;

                int score = Matching::MatchAlgorithm::calculateScore(currentUser, *candidatePtr);
                
                candidates.push_back({ *candidatePtr, score });
            }

            std::sort(candidates.begin(), candidates.end(), 
                [](const std::pair<User, int>& a, const std::pair<User, int>& b) {
                    return a.second > b.second; 
                }
            );
            
            return candidates;
        }

    bool UserManager::addLike(int senderId, int receiverId) {
        if (senderId == receiverId) return false;

        std::string sql = "INSERT OR IGNORE INTO LIKES (SENDER_ID, RECEIVER_ID) VALUES (" 
                        + std::to_string(senderId) + ", " + std::to_string(receiverId) + ");";
        
        try {
            db_.execute(sql);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool UserManager::addRejection(int senderId, int receiverId) {
        if (senderId == receiverId) {
            return false;
        }
        
        std::string sql = "INSERT OR IGNORE INTO REJECTIONS (SENDER_ID, RECEIVER_ID) VALUES (" 
                        + std::to_string(senderId) + ", " + std::to_string(receiverId) + ");";
        
        bool result = db_.execute(sql);

        return result;
    }

    bool UserManager::checkMatch(int senderId, int receiverId) {
        std::string sql = "SELECT COUNT(*) FROM LIKES WHERE SENDER_ID = " + std::to_string(receiverId) 
                        + " AND RECEIVER_ID = " + std::to_string(senderId) + ";";

        auto result = db_.query(sql);
        
        if (!result.empty() && !result[0].empty()) {
            int count = std::stoi(result[0][0]);
            return count > 0;
        }
        return false;
    }

    int UserManager::getLikeCount(int userId) {
        std::string sql = "SELECT COUNT(*) FROM LIKES WHERE RECEIVER_ID = " + std::to_string(userId) + ";";
        
        try {
            auto result = db_.query(sql);
            if (!result.empty() && !result[0].empty()) {
                return std::stoi(result[0][0]);
            }
        } catch (...) {
            return 0;
        }
        return 0;
    }

    std::vector<User> UserManager::getMatches(int currentUserId) {
        std::vector<User> matches;
        std::string sql = "SELECT * FROM USERS WHERE "
                        "ID IN (SELECT RECEIVER_ID FROM LIKES WHERE SENDER_ID = " + std::to_string(currentUserId) + ") "
                        "AND "
                        "ID IN (SELECT SENDER_ID FROM LIKES WHERE RECEIVER_ID = " + std::to_string(currentUserId) + ");";

        auto results = db_.query(sql);
        for (const auto& row : results) {
            auto userPtr = rowToUser(row);
            if (userPtr) matches.push_back(*userPtr);
        }
        return matches;
    }

    std::vector<User> UserManager::getAllUsers() {
        std::vector<User> allUsers;
        std::string sql = "SELECT * FROM USERS ORDER BY ID ASC;";
        
        auto results = db_.query(sql);

        for (const auto& row : results) {
            auto userPtr = rowToUser(row); 
            if (userPtr) {
                allUsers.push_back(*userPtr);
            }
        }
        return allUsers;
    }

}