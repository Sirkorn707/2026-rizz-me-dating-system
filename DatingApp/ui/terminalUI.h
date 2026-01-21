/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: terminalUI.h
    Description: Header file for the terminal user interface implementation.
*/
#ifndef UI_TERMINALUI_H
#define UI_TERMINALUI_H

#include "../user/userManager.h"
#include "../matching/messageManager.h"
#include "../user/user.h"

namespace UI {

    /* Class description: TerminalUI
        EN: Class implementing a terminal-based user interface for the dating application.
        PL: Klasa implementująca interfejs użytkownika oparty na terminalu dla aplikacji randkowej.
    */
    class TerminalUI {
    private:
        User::UserManager& userManager_;
        Matching::MessageManager& messageManager_;
        /* Function description: openChat()
            EN: Method to handle chat interface between the current user and a partner.
            PL: Metoda obsługująca interfejs czatu między aktualnym użytkownikiem a partnerem.
        */
        bool openChat(const User::User& currentUser, int partnerId, std::string partnerName);
        /* Function description: handleAccountOptions()
            EN: Method to manage account options like password change and account deletion.
            PL: Metoda do zarządzania opcjami konta, takimi jak zmiana hasła i usunięcie konta.
        */
        bool handleAccountOptions(User::User& currentUser);
        /* Function description: adminMenu()
            EN: Method to display and manage the administrator panel.
            PL: Metoda do wyświetlania i zarządzania panelem administratora.
        */
        void adminMenu();
    public:
        /* Function description: TerminalUI()
            EN: Constructor to initialize the terminal UI with user and message managers.
            PL: Konstruktor inicjujący interfejs terminalowy z menedżerami użytkowników i wiadomości.
        */
        TerminalUI(User::UserManager& userManager, Matching::MessageManager& messageManager);
        /* Function description: run()
            EN: Method to start the main terminal UI loop.
            PL: Metoda uruchamiająca główną pętlę interfejsu terminalowego.
        */
        void run();
        /* Function description: login()
            EN: Method to handle user login process.
            PL: Metoda obsługująca proces logowania użytkownika.
        */
        void login();
        /* Function description: registerUser()
            EN: Method to handle new user registration process.
            PL: Metoda obsługująca proces rejestracji nowego użytkownika.
        */
        void registerUser();
        /* Function description: showUserMenu()
            EN: Method to display and manage the user menu after login.
            PL: Metoda do wyświetlania i zarządzania menu użytkownika po zalogowaniu.
        */
        void showUserMenu(User::User& user);
    };

}

#endif