/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: messageManager.cpp
    Description: Implementation of the message manager.
*/
#include "MessageManager.h"
#include "../utils/HelperFunctions.h"
#include <iostream>
#include <string>

namespace Matching {

    MessageManager::MessageManager(Storage::Database& db) : db_(db) {
        // Code description: in constructor we make sure the MESSAGES table exists.
        std::string sql = "CREATE TABLE IF NOT EXISTS MESSAGES ("
                          "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "SENDER_ID INTEGER, "
                          "RECEIVER_ID INTEGER, "
                          "CONTENT TEXT, "
                          "TIMESTAMP DATETIME DEFAULT CURRENT_TIMESTAMP);";
        try {
            db_.execute(sql);
        } catch (...) {
            std::cerr << "[MessageManager] MESSAGES table creation error." << std::endl;
        }
    }

    void MessageManager::sendMessage(int senderId, int receiverId, const std::string& content) {
        if (content.empty()) return;

        // Code description: Sanitize content to prevent SQL injection. Deleting '' from content. More details in HelperFunctions.h.
        std::string safeContent = Utils::HelperFunctions::sanitize(content);
        std::string sql = "INSERT INTO MESSAGES (SENDER_ID, RECEIVER_ID, CONTENT) VALUES ("
                          + std::to_string(senderId) + ", "
                          + std::to_string(receiverId) + ", '"
                          + safeContent + "');";
        try {
            db_.execute(sql);
        } catch (const std::exception& e) {
            std::cerr << "[MessageManager] Writing error. Cannot save message. " << e.what() << std::endl;
        }
    }

    std::vector<Message> MessageManager::getConversation(int user1Id, int user2Id) {
        std::vector<Message> messages;

        // Code description: Download all messages between user1Id and user2Id, ordered by ID (chronologically).
        std::string u1 = std::to_string(user1Id);
        std::string u2 = std::to_string(user2Id);

        std::string sql = "SELECT ID, SENDER_ID, RECEIVER_ID, CONTENT FROM MESSAGES WHERE "
                          "(SENDER_ID = " + u1 + " AND RECEIVER_ID = " + u2 + ") "
                          "OR "
                          "(SENDER_ID = " + u2 + " AND RECEIVER_ID = " + u1 + ") "
                          "ORDER BY ID ASC;";
        try {
            auto results = db_.query(sql);
            for (const auto& row : results) {
                if (row.size() >= 4) {
                    try {
                        int id = std::stoi(row[0]);
                        int sender = std::stoi(row[1]);
                        int receiver = std::stoi(row[2]);
                        std::string content = row[3];
                        /* emplace_back() function usage
                            -> Constructs a Message object in place within the messages vector.
                            -> This avoids unnecessary copies and improves performance.
                            -> Difference from push_back(): push_back() would create a temporary Message object and then copy/move it into the vector.
                            ->                              emplace_back() constructs the object directly in the memory allocated for the vector.
                            -> More info: https://en.cppreference.com/w/cpp/container/vector/emplace_back.
                        */
                        messages.emplace_back(id, sender, receiver, content);
                    } catch (...) {
                        continue;
                    }
                }
            }
        } catch (...) {
            std::cerr << "[MessageManager] Blad odczytu wiadomosci." << std::endl;
        }

        return messages;
    }

    int MessageManager::getReceivedMessageCount(int userId) {
        // Code description: Count unread messages for the user (IS_READ = 0).
        std::string sql = "SELECT COUNT(*) FROM MESSAGES WHERE RECEIVER_ID=" 
                            + std::to_string(userId) + " AND IS_READ=0;";        
        auto result = db_.query(sql);
        
        if (!result.empty() && !result[0].empty()) {
            try {
                return std::stoi(result[0][0]);
            } catch (...) {
                return 0;
            }
        }
        return 0;
    }

    void MessageManager::markConversationAsRead(int userId, int partnerId) {
        // Code description: Mark all messages in the conversation as read (IS_READ = 1).
        std::string sql = "UPDATE MESSAGES SET IS_READ = 1 WHERE RECEIVER_ID = " 
                        + std::to_string(userId) + " AND SENDER_ID = " 
                        + std::to_string(partnerId) + ";";
        
        db_.execute(sql);
    }

}