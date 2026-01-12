/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: displayManager.h
    Description: Header file for the display manager implementation.
*/
#ifndef UI_DISPLAYMANAGER_H
#define UI_DISPLAYMANAGER_H

namespace Utils {

    /* Class description: DisplayManager
        EN: DisplayManager class for handling terminal display operations.
        PL: Klasa DisplayManager do obsługi operacji wyświetlania w terminalu.
    */
    class DisplayManager {
    public:
        /* Function description: clearScreen()
            EN: Static method to clear the terminal screen.
            PL: Metoda statyczna do czyszczenia ekranu terminala.
        */
        static void clearScreen();
        /* Function description: showAppName()
            EN: Static method to display the application name banner.
            PL: Metoda statyczna do wyświetlania banera z nazwą aplikacji.
        */
        static void showAppName();
        /* Function description: showMatchASCIIBanner()
            EN: Static method to display an ASCII art banner for a match.
            PL: Metoda statyczna do wyświetlania banera ASCII z informacją o matchu.
        */
        static void showMatchASCIIBanner();
    };

}

#endif