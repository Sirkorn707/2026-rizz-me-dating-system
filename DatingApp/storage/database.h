/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: database.h
    Description: Header file for the database management class.
*/
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include "../core/sqlite3.h" // SQLite3 library

namespace Storage {

    /* Type alias for query results. Used because data type is complex. */
    using QueryResult = std::vector<std::vector<std::string>>;

    /* Class description: Database
        EN: Class for managing SQLite database connection and operations.
        PL: Klasa do zarządzania połączeniem i operacjami na bazie danych SQLite.
    */
    class Database {
    public:
        /* Function description: Database()
            EN: Constructor opens the database connection.
            PL: Konstruktor otwiera połączenie z bazą danych.
        */
        Database(const std::string& dbPath);

        /* Function description: ~Database()
            EN: Destructor closes the database connection.
            PL: Destruktor zamyka połączenie z bazą danych.
        */
        ~Database();

        /* Function description: initialize()
            EN: Initializes database tables if they do not exist.
            PL: Inicjalizuje tabele bazy danych, jeśli nie istnieją.
        */
        void initialize();

        /* Function description: execute()
            EN: Executes a SQL statement (CREATE, INSERT, UPDATE, DELETE).
            PL: Wykonuje zapytanie SQL (CREATE, INSERT, UPDATE, DELETE).
        */
        bool execute(const std::string& sql);

        /* Function description: query()
            EN: Executes a SQL query (SELECT) and returns results.
            PL: Wykonuje zapytanie SQL (SELECT) i zwraca wyniki.
        */
        QueryResult query(const std::string& sql);

    private:
        sqlite3* db_; // Pointer to SQLite database
        bool isConnected_;

        /* Function description: callback()
            EN: Static callback helper function for processing query results.
            PL: Statyczna funkcja pomocnicza callback do przetwarzania wyników zapytań.
        */
        static int callback(void* data, int argc, char** argv, char** azColName);
    };

}

#endif