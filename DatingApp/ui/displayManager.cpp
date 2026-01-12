/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: displayManager.cpp
    Description: Implementation file for the display manager.
*/
#include "DisplayManager.h"
#include <iostream>
#include <cstdlib> // Used functions: std::system

namespace Utils {

    void DisplayManager::clearScreen() {
        #ifdef _WIN32
            std::system("cls");
        #else
            std::system("clear");
        #endif
    }

    void DisplayManager::showAppName() {
        std::cout << R"(
    ██████╗ ██╗███████╗███████╗    ███╗   ███╗███████╗
    ██╔══██╗██║╚══███╔╝╚══███╔╝    ████╗ ████║██╔════╝
    ██████╔╝██║  ███╔╝   ███╔╝     ██╔████╔██║█████╗  
    ██╔══██╗██║ ███╔╝   ███╔╝      ██║╚██╔╝██║██╔══╝  
    ██║  ██║██║███████╗███████╗    ██║ ╚═╝ ██║███████╗
    ╚═╝  ╚═╝╚═╝╚══════╝╚══════╝    ╚═╝     ╚═╝╚══════╝
        )" << std::endl;
    }

    void DisplayManager::showMatchASCIIBanner() {
        std::cout << R"(
        .·:*¨¨* ≈☆≈ *¨¨*:·.
    .·:*¨¨* ≈☆≈ *¨¨*:·.
    .·:*¨¨* ≈☆≈ *¨¨*:·.

    ██╗ ████████╗   '   ███████╗    █████╗ 
    ██║ ╚══██╔══╝       ██╔════╝   ██╔══██╗
    ██║    ██║          ███████╗   ███████║
    ██║    ██║          ╚════██║   ██╔══██║
    ██║    ██║          ███████║   ██║  ██║
    ╚═╝    ╚═╝          ╚══════╝   ╚═╝  ╚═╝
    ███╗   ███╗ █████╗ ████████╗ ██████╗██╗  ██╗
    ████╗ ████║██╔══██╗╚══██╔══╝██╔════╝██║  ██║
    ██╔████╔██║███████║   ██║   ██║     ███████║
    ██║╚██╔╝██║██╔══██║   ██║   ██║     ██╔══██║
    ██║ ╚═╝ ██║██║  ██║   ██║   ╚██████╗██║  ██║
    ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝╚═╝  ╚═╝

        .·:*¨¨* ≈☆≈ *¨¨*:·.
    .·:*¨¨* ≈☆≈ *¨¨*:·.
    .·:*¨¨* ≈☆≈ *¨¨*:·.
        )" << std::endl;
    }
}