/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: database.cpp
    Description: Implementation file for the database management class.
*/
#include "Database.h"
#include <iostream>

namespace Storage {

    Database::Database(const std::string& dbPath) : db_(nullptr), isConnected_(false) {
        // Code description: Connection to SQLite database.
        int exit = sqlite3_open(dbPath.c_str(), &db_);

        if (exit != SQLITE_OK) {
            std::cerr << "[Database] Database opening error. " << sqlite3_errmsg(db_) << std::endl;
            isConnected_ = false;
        } else {
            isConnected_ = true;
        }
    }

    Database::~Database() {
        if (isConnected_ && db_) {
            sqlite3_close(db_);
        }
    }
    
    void Database::initialize() {
        // USERS Table
        execute("CREATE TABLE IF NOT EXISTS USERS ("
                "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                "USERNAME TEXT NOT NULL UNIQUE, "
                "PASSWORD_HASH TEXT NOT NULL, "
                "AGE INT NOT NULL, "
                "DESCRIPTION TEXT, "
                "GENDER INT, "
                "INTERESTS TEXT);");

        // LIKES Table
        execute("CREATE TABLE IF NOT EXISTS LIKES ("
                "SENDER_ID INTEGER, "
                "RECEIVER_ID INTEGER, "
                "PRIMARY KEY (SENDER_ID, RECEIVER_ID), "
                "FOREIGN KEY(SENDER_ID) REFERENCES USERS(ID), "
                "FOREIGN KEY(RECEIVER_ID) REFERENCES USERS(ID));");

        // MESSAGES Table
        execute("CREATE TABLE IF NOT EXISTS MESSAGES ("
                "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                "SENDER_ID INTEGER, "
                "RECEIVER_ID INTEGER, "
                "CONTENT TEXT, "
                "TIMESTAMP DATETIME DEFAULT CURRENT_TIMESTAMP, "
                "IS_READ INTEGER DEFAULT 0, "
                "FOREIGN KEY(SENDER_ID) REFERENCES USERS(ID), "
                "FOREIGN KEY(RECEIVER_ID) REFERENCES USERS(ID));");

         // REJECTIONS Table
        execute("CREATE TABLE IF NOT EXISTS REJECTIONS ("
                "SENDER_ID INTEGER, "
                "RECEIVER_ID INTEGER, "
                "PRIMARY KEY (SENDER_ID, RECEIVER_ID));");      
    }

    bool Database::execute(const std::string& sql) {
        if (!isConnected_) return false;

        char* messageError;
        int exit = sqlite3_exec(db_, sql.c_str(), nullptr, 0, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "[Database] SQL Error (Execute). " << messageError << std::endl;
            sqlite3_free(messageError);
            return false;
        }
        return true;
    }

    int Database::callback(void* data, int argc, char** argv, char** azColName) {
        /* Code description: callback is used to process every row 
            the void* pointer 'data' is cast back to QueryResult* to store results.
        */
        QueryResult* results = static_cast<QueryResult*>(data);
        
        std::vector<std::string> row;
        for (int i = 0; i < argc; i++) {
            row.push_back(argv[i] ? argv[i] : "NULL");
            (void)azColName; // Code description: avoiding unused parameter warning
        }
        results->push_back(row); // Code description: push_back() here because we operate on existing variable (instead of emplace_back())
        return 0;
    }

    QueryResult Database::query(const std::string& sql) {
        QueryResult results;
        if (!isConnected_) return results;

        char* messageError;
        /* Code description: 3rd argument goes to vector address.
            callback function can access it.
        */
        int exit = sqlite3_exec(db_, sql.c_str(), callback, &results, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "[Database] SQL Error (Query). " << messageError << std::endl;
            sqlite3_free(messageError);
        }

        return results;
    }

}