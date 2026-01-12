/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: message.h
    Description: Header file for the message class.
*/
#ifndef MATCHING_MESSAGE_H
#define MATCHING_MESSAGE_H

#include <string>

namespace Matching {

    /* Class description: Message
        EN: Class representing a single message between users.
        PL: Klasa reprezentująca pojedynczą wiadomość między użytkownikami.
    */
    class Message {
    public:
        /* Function description: Message()
            EN: Constructor to initialize a message object.
            PL: Konstruktor inicjujący obiekt wiadomości.
        */
        Message(int id, int senderId, int receiverId, std::string content)
            : id_(id), senderId_(senderId), receiverId_(receiverId), content_(std::move(content)) {}

        /* Functions description: Getters
            EN: Methods to access message properties.
            PL: Metody dostępu do właściwości wiadomości.

            Getters:
                - getId(): Returns the message ID.
                - getSenderId(): Returns the sender's user ID.
                - getReceiverId(): Returns the receiver's user ID.
                - getContent(): Returns the message content.
        */
        int getId() const { return id_; }
        int getSenderId() const { return senderId_; }
        int getReceiverId() const { return receiverId_; }
        std::string getContent() const { return content_; }

    private:
        int id_;
        int senderId_;
        int receiverId_;
        std::string content_;
    };

}

#endif