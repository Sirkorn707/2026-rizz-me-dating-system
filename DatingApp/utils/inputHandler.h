/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: inputHandler.h
    Description: Header file for the input handler implementation.
*/
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>
#include <iostream>

namespace Utils {

    /* Class description: InputHandler
        EN: Class for handling user input from the terminal.
        PL: Klasa do obsługi wejścia użytkownika z terminala.
    */
    class InputHandler {
    public:
        /* Function description: getInt()
            EN: Static method to get an integer from user input with error handling.
            PL: Metoda statyczna pobierająca liczbę całkowitą z wejścia użytkownika z obsługą błędów.

            Additional description:
                -> The method prompts the user for input and attempts to read an integer.
                -> If the input is invalid (not an integer), it informs the user and allows for retries.
                -> After a specified number of failed attempts, it throws an exception.
        */
        static int getInt(const std::string& prompt, int maxAttempts = 5);

        /* Function description: getString()
            EN: Static method to get a single word string from user input.
            PL: Metoda statyczna pobierająca pojedynczy wyraz ze wejścia użytkownika.
        */
        static std::string getString(const std::string& prompt);

        /* Function description: getLine()
            EN: Static method to get a full line string from user input.
            PL: Metoda statyczna pobierająca pełną linię tekstu z wejścia użytkownika.
        */
        static std::string getLine(const std::string& prompt);

        /* Function description: getPasswordHidden()
            EN: Static method to get a password input from the user without echoing it to the terminal.
            PL: Metoda statyczna pobierająca hasło od użytkownika bez wyświetlania go w terminalu.
        */
        static std::string getPasswordHidden(const std::string& prompt);
    };

}

#endif