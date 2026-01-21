/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: messageManager.h
    Description: Header file for the message manager implementation.
*/
#ifndef MATCHING_MESSAGEMANAGER_H
#define MATCHING_MESSAGEMANAGER_H

#include <string>
#include <vector>
#include "../storage/database.h"
#include "message.h"

namespace Matching {

    /* Class description: MessageManager
        EN: Class responsible for managing messages between users.
        PL: Klasa odpowiedzialna za zarządzanie wiadomościami między użytkownikami.
    */
    class MessageManager {
    private:
        Storage::Database& db_;
    public:
        /* Function description: MessageManager()
            EN: Constructor to initialize the message manager with a database reference.
            PL: Konstruktor inicjujący menedżera wiadomości z referencją do bazy danych.

            Additional description:
            -> 'explicit' was used to prevent automatic conversions of the object 'Database' to 'MessageManager'.
            -> This avoids unintended bugs in the code. It also helps the compilator optimize the code better.
            -> More information: https://en.cppreference.com/w/cpp/language/explicit.html
        */
        explicit MessageManager(Storage::Database& db);

        /* Function description: sendMessage()
            EN: Method to send a message from one user to another.
            PL: Wysyłanie wiadomości od jednego użytkownika do drugiego.
        */
        void sendMessage(int senderId, int receiverId, const std::string& content);

        /* Function description: getConversation()
            EN: Method to retrieve the conversation between two users.
            PL: Pobieranie rozmowy między dwoma użytkownikami.

            Additional description:
            -> returns a vector of Message objects representing the conversation between users.
        */
        std::vector<Message> getConversation(int user1Id, int user2Id);

        /* Functions description: getReceivedMessageCount() and markConversationAsRead()
            EN: Additional methods for message management.
            PL: Dodatkowe metody do zarządzania wiadomościami.

            -> getReceivedMessageCount(): Returns the count of unread messages for a user.
            -> markConversationAsRead(): Marks all messages in a conversation as read.
        */
        int getReceivedMessageCount(int userId);
        void markConversationAsRead(int userId, int partnerId);
    };

}

#endif