/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: main.cpp
    Description: THE MAIN file for the Rizz.me Dating Application.
*/

/* System Headers: */
#include <iostream>
/* Windows-specific Headers */
#ifdef _WIN32
    #include <windows.h>
#endif
/* Storage Headers: */
#include "storage/database.h"
/* User Headers: */
#include "user/userManager.h"
#include "user/user.h"
/* Matching Headers */
#include "matching/messageManager.h"
/* UI Headers: */
#include "ui/terminalUI.h"
/* Utils Headers: */
#include "utils/testData.h"
#include "utils/colors.h"

/* THE Main Function :D */
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    try {
        // Code description: DATABASE INITIALIZATION
        Storage::Database db("../data/dating_app.db");
        db.initialize();

        // Code description: MANAGERS INITIALIZATION
        User::UserManager userManager(db);
        Matching::MessageManager messageManager(db);

        // Code description: LOAD TEST DATA
        Utils::loadTestData(userManager);

        // Code description: UI INITIALIZATION
        UI::TerminalUI ui(userManager, messageManager);

        // Code description: RUN THE APPLICATION
        ui.run();

    } catch (const std::exception& e) {
        std::cerr << "Wystąpił krytyczny błąd poczas inicjalizacji aplikacji. Rodzaj błędu: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}