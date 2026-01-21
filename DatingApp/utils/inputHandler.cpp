/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: inputHandler.cpp
    Description: Implementation file for the input handler.
*/
#include "inputHandler.h"
#include <iostream>
#include <limits> // Used functions: std::numeric_limits, std::streamsize

#ifdef _WIN32
    #include <conio.h> // Windows: _getch()
#else
    #include <termios.h> // Linux/Mac: echo control
    #include <unistd.h> // Used functions: STDIN_FILENO
#endif

namespace Utils {

    int InputHandler::getInt(const std::string& prompt, int maxAttempts) {
        int value;
        int attempts = 0;

        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                attempts++;

                std::cout << "--> Error. Not an integer. (" 
                          << attempts << "/" << maxAttempts << ")" << std::endl;
                
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (attempts >= maxAttempts) {
                    throw std::runtime_error("Data entry limit has been exceeded.");
                }
            }
        }
    }

    std::string InputHandler::getString(const std::string& prompt) {
        std::string value;
        std::cout << prompt;
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        return value;
    }

    std::string InputHandler::getLine(const std::string& prompt) {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    }

    std::string InputHandler::getPasswordHidden(const std::string& prompt) {
        std::cout << prompt;
        std::string password;

        /* Code description: 
            -> Platform-specific implementation to hide password input.
            -> On Windows, uses _getch() to read characters without echoing.
            -> Linux/macOS uses termios to disable terminal echo.
        */
        #ifdef _WIN32
            char ch;
            while (true) {
                ch = _getch();
                
                if (ch == 13) { // Code description: Enter key (kod 13)
                    std::cout << std::endl;
                    break;
                } else if (ch == 8) { // Code description: Backspace key (kod 8)
                    if (!password.empty()) {
                        password.pop_back();
                        std::cout << "\b \b";
                    }
                } else {
                    password += ch;
                    std::cout << '*';
                }
            }
        #else
            /* Code description: 
                Code below structure:
                -> Download current terminal settings
                -> Disable echo
                -> Apply new settings
                -> Read password input
            */
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            std::cin >> password;
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            std::cout << std::endl; 
        #endif

        return password;
    }

}