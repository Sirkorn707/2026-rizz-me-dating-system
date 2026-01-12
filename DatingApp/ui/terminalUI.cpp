/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: terminalUI.cpp
    Description: Implementation file for the terminal user interface.
*/
#include "TerminalUI.h"
#include "DisplayManager.h"
#include "../utils/InputHandler.h"
#include "../utils/HelperFunctions.h"
#include "../security/passwordManager.h"
#include <iostream>
#include <sstream> // Used functions: std::stringstream
#include <iomanip> // Used functions: std::setw

namespace UI {

    TerminalUI::TerminalUI(User::UserManager& userManager, Matching::MessageManager& messageManager)
        : userManager_(userManager), messageManager_(messageManager) {
    }

    void TerminalUI::run() {
        while (true) {
            Utils::DisplayManager::clearScreen();
            
            std::cout << "\n==========================================================" << std::endl;
            Utils::DisplayManager::showAppName();
            std::cout << "==========================================================" << std::endl;
            std::cout << "\nŁadowanie miłości... ████████ 100%\n" << std::endl;
            std::cout << " (1) Logowanie." << std::endl;
            std::cout << " (2) Rejestracja konta." << std::endl;
            std::cout << " (3) Wyjście z aplikacji." << std::endl;
            
            int choice = Utils::InputHandler::getInt("Wybrana opcja -> ");

            if (choice == 1) {
                login();
            } else if (choice == 2) {
                registerUser();
            } else if (choice == 3) {
                std::cout << "Randkowanie offline? Powodzenia :)" << std::endl;
                break;
            }
        }
    }

    void TerminalUI::login() {
        Utils::DisplayManager::clearScreen();
        
        std::cout << "┌─────────────────┐\n";
        std::cout << "│    LOGOWANIE    │\n";
        std::cout << "└─────────────────┘\n";
        std::string username = Utils::InputHandler::getLine("Login: ");
        std::string rawPassword = Utils::InputHandler::getPasswordHidden("Hasło: ");

        if (username == "admin" && rawPassword == "admin") {
            std::cout << "\n[SYSTEM] Witaj administratorze. Czas na zabawę! " << std::endl;
            std::cout << "\n[SYSTEM] Szukam idealnej kompilacji... " << std::endl;
            Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby rozpocząć zabawę użytkownikami... ");
            adminMenu();
            return;
        }
        
        std::string passwordHash = Security::PasswordManager::hashPassword(rawPassword);

        if (userManager_.login(username, passwordHash)) {
            std::cout << "Zalogowano pomyślnie! Czas znaleźć drugą połówkę! " << std::endl;
            Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby przejść do swojego konta...");
            try {
                auto userPtr = userManager_.getUserByUsername(username);

                if (userPtr) {
                    showUserMenu(*userPtr);
                } else {
                    std::cout << "[SYSTEM ERROR] Nie udało się pobrać profilu po zalogowaniu. " << std::endl;
                    Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby wrócić do menu i spróbuj ponownie... ");
                }
                
            } catch (const std::exception& e) {
                std::cout << "[SYSTEM ERROR] Nie udało się pobrać profilu. " << e.what() << std::endl;
                Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby wrócić do menu...");
            }
        } else {
            std::cout << "[LOGIN ERROR] Błędny login lub hasło. " << std::endl;
            Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby wrócić do menu głównego i spróbować ponownie...");
        }
    }

    void TerminalUI::registerUser() {
        Utils::DisplayManager::clearScreen();
        
        std::cout << "╔══════════════════╗\n";
        std::cout << "║   REJESTRACJA    ║\n";
        std::cout << "╚══════════════════╝\n";
        try {
            /* Code description: LOGIN validation*/
            std::string username;
            while (true) {
                username = Utils::InputHandler::getLine("Podaj swój login (min. 3 znaki!): ");
                if (username.length() >= 3) {
                    break;
                }
                std::cout << "[REGISTER ERROR] Login jest za krótki! Wpisz CO NAJMNIEJ 3 znaki." << std::endl;
            }

            /* Code description: PASSWORD validation */
            std::string rawPassword;
            while (true) {
                rawPassword = Utils::InputHandler::getPasswordHidden("Podaj swoje hasło (min. 4 znaki!): ");
                if (rawPassword.length() >= 4) {
                    break;
                }
                std::cout << "[REGISTER ERROR] Hasło jest za krótkie! Wpisz CO NAJMNIEJ 4 znaki." << std::endl;
            }

            std::string passwordHash = Security::PasswordManager::hashPassword(rawPassword);

            /* Code description: AGE validation */
            int age = Utils::InputHandler::getInt("Podaj swój wiek: ");

            if (age < 18) {
                std::cout << "\n[REGISTER ERROR] Przykro mi, aplikacja jest dostępna tylko dla osób pełnoletnich (18+)." << std::endl;
                std::cout << "Skończ 18 lat i wróć do aplikacji." << std::endl;
                Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby wrócić do menu głównego...");
                return;
            }
            if (age > 120) {
                 std::cout << "\n[REGISTER ERROR] Podano nierealny wiek. Wybacz, jeśli jesteś Jeanne Calment, w przeciwnym wypadku wpisz poprawny wiek." << std::endl;
                 Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby wrócić do menu głównego...");
                 return;
            }

            /* Code description: GENDER selection */
            User::Gender selectedGender;
            while(true) {
                std::cout << "\n[SYSTEM] Wybierz swoją płeć (Uwaga: Możesz to zrobić TYLKO RAZ):" << std::endl;
                std::cout << " (1) Mężczyzna" << std::endl;
                std::cout << " (2) Kobieta" << std::endl;
                std::cout << " (3) Inne / Helikopter bojowy" << std::endl;
                
                int gChoice = Utils::InputHandler::getInt("Wybrana opcja -> ");

                if (gChoice == 1) { selectedGender = User::Gender::Male; break; }
                else if (gChoice == 2) { selectedGender = User::Gender::Female; break; }
                else if (gChoice == 3) { selectedGender = User::Gender::Other; break; }
                else { std::cout << "[GENDER ERROR] Niepoprawna opcja. Spróbuj 1, 2 lub 3." << std::endl; }
            }

            /* Code description: CREATE PROFILE */
            User::Profile profile(age, "", selectedGender, {});
            User::User newUser(-1, username, passwordHash, profile);

            if (userManager_.registerUser(newUser)) {
                std::cout << "\n[SYSTEM] Hej, HEJ, HEEEEJ! Konto utworzone! Możesz się zalogować i znaleźć miłość!" << std::endl;
            } else {
                std::cout << "\n[REGISTER ERROR] Login '" << username << "' jest juz zajęty. Wybierz inny." << std::endl;
            }

        } catch (const std::exception& e) {
            /* Code description: error occurs when an error occured 5 times */
            std::cout << "\n[SYSTEM ERROR] " << e.what() << std::endl;
            std::cout << "Wyczerpano ilość prób. Rejestracja przerwana." << std::endl;
        }
        Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby wrócić do menu głównego i spróbuj ponownie...");
    }

    void TerminalUI::showUserMenu(User::User& user) {
        bool loggedIn = true;
        while (loggedIn) {
            Utils::DisplayManager::clearScreen();
            
            std::cout << "╔════════════════╗\n";
            std::cout << "║   MOJE KONTO   ║\n";
            std::cout << "╚════════════════╝\n";
            
            int msgCount = messageManager_.getReceivedMessageCount(user.getId());
            if (msgCount > 0) {
                std::cout << "\n   <----- MASZ NOWE WIADOMOŚCI (" << msgCount << ") ----->   \n" << std::endl;
            }

            std::cout << "\n--- ZALOGOWANY JAKO: " << user.getUsername() << " ---" << std::endl;
            std::cout << " (1) Mój Profil" << std::endl;
            std::cout << " (2) Szukaj miłości swojego życia" << std::endl;
            std::cout << " (3) Wiadomości" << std::endl;
            std::cout << " (4) Opcje Konta " << std::endl;
            std::cout << " (5) Wyloguj się" << std::endl;
            int choice = Utils::InputHandler::getInt("Wybrana opcja -> ");

            switch (choice) {
                case 1: { // PROFILE VIEW & EDIT
                    bool watchingProfile = true;
                    while(watchingProfile) {
                        Utils::DisplayManager::clearScreen();
                        std::cout << "\n=== MOJ PROFIL ===" << std::endl;
                        std::cout << "Login: " << user.getUsername() << std::endl;
                        std::cout << "Wiek:  " << user.getProfile().getAge() << std::endl;                        
                        
                        std::cout << "Płeć:  ";
                        auto gend = user.getProfile().getGender();
                        if (gend == User::Gender::Male) std::cout << "Mężczyzna";
                        else if (gend == User::Gender::Female) std::cout << "Kobieta";
                        else std::cout << "Inne/Helikopter bojowy";
                        std::cout << std::endl;

                        std::cout << "Rizz (Ilość polubień profilu): " << userManager_.getLikeCount(user.getId()) << std::endl;
                        
                        std::string desc = user.getProfile().getDescription();
                        std::cout << "Opis:  " << (desc.empty() ? "(brak)" : desc) << std::endl;
                        
                        std::cout << "Hobby: ";
                        if (user.getProfile().getInterests().empty()) {
                            std::cout << "(brak)";
                        } else {
                            for (const auto& i : user.getProfile().getInterests()) std::cout << i << ", ";
                        }
                        std::cout << "\n-----------------------------------" << std::endl;
                        
                        std::cout << "[E] Edytuj profil  |  [0] Wroc do menu glownego" << std::endl;
                        std::string action = Utils::InputHandler::getLine("Wybrana opcja -> ");

                        if (action == "0") {
                            watchingProfile = false;
                        } 
                        else if (action == "e" || action == "E") {
                            bool editing = true;
                            while(editing) {
                                Utils::DisplayManager::clearScreen();
                                std::cout << "\n--- EDYCJA PROFILU ---" << std::endl;
                                std::cout << " (1) Edytuj Opis (Bio)" << std::endl;
                                std::cout << " (2) Edytuj Hobby" << std::endl;
                                std::cout << " (3) Edytuj Wiek" << std::endl;
                                std::cout << "----------------------" << std::endl;
                                std::cout << " (9) ZAPISZ ZMIANY (Wyslij do bazy)" << std::endl;
                                std::cout << " (0) Anuluj i wyjdz" << std::endl;
                                
                                int editChoice = Utils::InputHandler::getInt("Wybrana opcja -> ");

                                switch(editChoice) {
                                    case 1: {
                                        std::cout << "Obecny opis: " << user.getProfile().getDescription() << std::endl;
                                        std::string newDesc = Utils::InputHandler::getLine("Nowy opis: ");
                                        user.getProfile().setDescription(newDesc);
                                        std::cout << "[SYSTEM] Opis twojego profilu został zmieniony." << std::endl;
                                        Utils::HelperFunctions::sleep(500);
                                        break;
                                    }
                                    case 2: {
                                        std::cout << "Wpisz nowe hobby oddzielone przecinkami (np. narty,kino):" << std::endl;
                                        std::string raw = Utils::InputHandler::getLine("> ");
                                        auto newVec = Utils::HelperFunctions::splitString(raw, ',');
                                        user.getProfile().setInterestsVector(newVec);
                                        std::cout << "[SYSTEM] Hobby zmienione." << std::endl;
                                        Utils::HelperFunctions::sleep(500);
                                        break;
                                    }
                                    case 3: {
                                        int newAge = Utils::InputHandler::getInt("Podaj nowy wiek: ");
                                        if (newAge >= 18 && newAge < 120) {
                                            user.getProfile().setAge(newAge);
                                            std::cout << "[SYSTEM] Wiek zmieniony." << std::endl;
                                        } else {
                                            std::cout << "[SYSTEM ERROR] Nieprawidlowy wiek!" << std::endl;
                                            Utils::HelperFunctions::sleep(1000);
                                        }
                                        break;
                                    }
                                    case 9: {
                                        if (userManager_.updateUser(user)) {
                                            std::cout << "\n[SYSTEM] Dane zapisane w bazie!" << std::endl;
                                            Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby kontynuować...");
                                            editing = false;
                                        } else {
                                            std::cout << "\n[SYSTEM ERROR] Nie udalo sie zapisac w bazie." << std::endl;
                                            Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby kontynuować...");
                                        }
                                        break;
                                    }
                                    case 0: {
                                        auto freshUser = userManager_.getUserByUsername(user.getUsername());
                                        if (freshUser) {
                                            user = *freshUser; 
                                        }
                                        std::cout << "[SYSTEM] Zmiany zostały odrzucone." << std::endl;
                                        editing = false;
                                        break;
                                    }
                                    default:
                                        std::cout << "[SYSTEM ERROR] Nieznana opcja." << std::endl;
                                }
                            }
                        }
                    }
                    break;
                }
                case 2: { // SEARCH FOR MATCHES
                    auto matches = userManager_.getPotentialMatches(user);
                    
                    if (matches.empty()) {
                        Utils::DisplayManager::clearScreen();
                        std::cout << "\n=============================================" << std::endl;
                        std::cout << " BRAK NOWYCH OSÓB DO SWIPOWANIA :(" << std::endl;
                        std::cout << "=============================================" << std::endl;
                        std::cout << "Przejrzano wszystkie dostepne profile\nw Twojej okolicy" << std::endl;
                        std::cout << "Spróbuj ponownie później." << std::endl;
                        std::cout << "=============================================" << std::endl;
                        Utils::InputHandler::getLine("\n[Enter] Wciśnij 'Enter', aby kontynuować...");
                    } else {
                        for (const auto& entry : matches) {
                            User::User candidate = entry.first;
                            int score = entry.second;
                            
                            Utils::DisplayManager::clearScreen();
                            std::cout << "\n===============================" << std::endl;
                            std::cout << "       \u2665ZGODNOŚĆ\u2665: " << score << "%" << std::endl;
                            std::cout << "===============================" << std::endl;
                            
                            std::cout << "Nick: " << candidate.getUsername() << std::endl;
                            std::cout << "Wiek: " << candidate.getProfile().getAge() << std::endl;
                            std::cout << "Opis: " << candidate.getProfile().getDescription() << std::endl;
                            
                            std::cout << "Zainteresowania: ";
                            for(const auto& i : candidate.getProfile().getInterests()) {
                                std::cout << i << " ";
                            }
                            std::cout << "\n-------------------------------" << std::endl;

                            std::cout << "[t] Tak (Swipe Right) | [n] Nie (Swipe Left) | [q] Wyjdz: ";
                            std::string dec = Utils::InputHandler::getLine("");

                            if (dec == "t" || dec == "T") {
                                userManager_.addLike(user.getId(), candidate.getId());
                                
                                if (userManager_.checkMatch(user.getId(), candidate.getId())) {
                                    Utils::DisplayManager::showMatchASCIIBanner();
                                    Utils::InputHandler::getLine("\n[Enter] Wciśnij 'Enter', aby kontynuować przeglądanie osób...");
                                }
                            } 
                            else if (dec == "n" || dec == "N") {
                                userManager_.addRejection(user.getId(), candidate.getId());                              
                            } 
                            else if (dec == "q" || dec == "Q") {
                                break;
                            }
                        }
                    }
                    break;
                }
                case 3: { // MESSAGES
                    bool stayingInMessages = true;
                    
                    while (stayingInMessages) {
                        Utils::DisplayManager::clearScreen();
                        auto matches = userManager_.getMatches(user.getId());
                        
                        if (matches.empty()) {
                            std::cout << "\nNie masz jeszcze pary do czatu. Próbuj dalej!" << std::endl;
                            Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby wyjść do menu...");
                            stayingInMessages = false;
                        } else {
                            std::cout << "\n=== TWOJE PARY ===" << std::endl;
                            for (const auto& m : matches) {
                                std::cout << "ID: " << m.getId() << " | " << m.getUsername() << std::endl;
                            }
                            
                            std::cout << "\n-----------------------------------" << std::endl;
                            std::cout << "Aby wejść do czatu, wpisz ID osoby." << std::endl;
                            std::cout << "Aby wrócić do menu głównego, wpisz '0'." << std::endl;
                            
                            int pid = Utils::InputHandler::getInt("Wybrane ID (lub WYJŚCIE) -> ");
                            
                            if (pid == 0) {
                                stayingInMessages = false;
                            } else {
                                std::string pName = "";
                                bool found = false;
                                for (const auto& m : matches) {
                                    if (m.getId() == pid) {
                                        found = true;
                                        pName = m.getUsername();
                                        break;
                                    }
                                }

                                if (found) {
                                    bool backToList = openChat(user, pid, pName);
                                    
                                    if (!backToList) {
                                        stayingInMessages = false;
                                    }
                                } else {
                                    std::cout << "To ID nie należy do Twoich par!" << std::endl;
                                    Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby kontynuować...");
                                }
                            }
                        }
                    }
                    break;
                }
                case 4: { // ACCOUNT OPTIONS
                    if (handleAccountOptions(user)) {
                        loggedIn = false; 
                    }
                    break;
                }
                case 5:
                    loggedIn = false;
                    break;
            }
        }
    }

    bool TerminalUI::openChat(const User::User& currentUser, int partnerId, std::string partnerName) {
        /* Code description: this appears only when user has new message*/
        messageManager_.markConversationAsRead(currentUser.getId(), partnerId);
        
        while (true) {
            Utils::DisplayManager::clearScreen(); 
            std::cout << "========================================" << std::endl;
            std::cout << " ROZMOWA Z: " << partnerName << " (ID: " << partnerId << ")" << std::endl;
            std::cout << "========================================" << std::endl;

            auto messages = messageManager_.getConversation(currentUser.getId(), partnerId);

            if (messages.empty()) {
                std::cout << "  (Cisza tu jak makiem zasiał... Napisz coś, aby przełamać lód!)" << std::endl;
            } else {
                for (const auto& msg : messages) {
                    if (msg.getSenderId() == currentUser.getId()) {
                        std::cout << "[JA]: " << msg.getContent() << std::endl;
                    } else {
                        std::cout << "[" << partnerName << "]: " << msg.getContent() << std::endl;
                    }
                }
            }
            std::cout << "========================================" << std::endl;
            std::cout << "[Napisz wiadomość] lub wpisz jedną z poniższych komend:" << std::endl;
            std::cout << "  /back - Powrót do listy par" << std::endl;
            std::cout << "  /exit - Wyjście do menu głównego" << std::endl;
            std::cout << "  [ENTER] - Odśwież czat" << std::endl;
            
            std::string content = Utils::InputHandler::getLine("> ");

            if (content == "/back" || content == "back") {
                return true;
            }
            if (content == "/exit" || content == "exit") {
                return false;
            }

            if (!content.empty()) {
                messageManager_.sendMessage(currentUser.getId(), partnerId, content);
            }
            /* IMPORTANT NOTE:
                If content is empty (just ENTER), the loop simply refreshes the view
            */
        }
    }

    bool TerminalUI::handleAccountOptions(User::User& currentUser) {
        while (true) {
            Utils::DisplayManager::clearScreen();

            std::cout << "╔════════════════╗\n";
            std::cout << "║   MOJE KONTO   ║\n";
            std::cout << "╚════════════════╝\n";

            std::cout << " OPCJE KONTA (" << currentUser.getUsername() << ") " << std::endl;
            std::cout << " (1) Zmień hasło" << std::endl;
            std::cout << " (2) Usuń konto" << std::endl;
            std::cout << " (3) Wróć" << std::endl;

            int choice = Utils::InputHandler::getInt("Wybierz opcje: ");

            if (choice == 1) {
                std::cout << "\n--- ZMIANA HASLA ---" << std::endl;
                std::string newRawPass;
                while(true) {
                    newRawPass = Utils::InputHandler::getPasswordHidden("Podaj nowe hasło (min. 4 znaki): ");
                    if (newRawPass.length() >= 4) break;
                    std::cout << "[SYSTEM ERROR] Nowe hasło jest za krótkie." << std::endl;
                }

                std::string newPassHash = Security::PasswordManager::hashPassword(newRawPass);
                if (userManager_.changePassword(currentUser.getId(), newPassHash)) {
                    std::cout << "[SYSTEM] Twoje hasło zostało zmienione!" << std::endl;
                }
                Utils::InputHandler::getLine("[Enter] powrot...");

            } else if (choice == 2) {
                std::cout << "\n[SYSTEM] Czy jesteś pewien, że chcesz usunąć konto? Tej operacji nie da się cofnąć." << std::endl;
                std::string confirm = Utils::InputHandler::getLine("Wpisz podaną wiadomość, jeśli chcesz potwierdzić usunięcie konta: 'TAK' ");

                if (confirm == "TAK") {
                    if (userManager_.deleteAccount(currentUser.getId())) {
                        std::cout << "\n[SYSTEM] Twoje konto zostało pomyślnie usunięte. Zostaniesz wylogowany i przeniesiony do menu głównego." << std::endl;
                        Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby kontynuować...");
                        return true;
                    }
                } else {
                    std::cout << "Wpisane słowo nie jest podanym słowem. Powrót do menu." << std::endl;
                    Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby kontynuować...");
                }

            } else if (choice == 3) {
                return false;
            }
        }
    }

    void TerminalUI::adminMenu() {
        int choice = -1;
        
        while (choice != 0) {
            Utils::DisplayManager::clearScreen();
            
            std::cout << "╔══════════════════╗\n";
            std::cout << "║   PANEL ADMINA   ║\n";
            std::cout << "╚══════════════════╝\n";
            
            auto users = userManager_.getAllUsers(); 

            if (users.empty()) {
                std::cout << "[SYSTEM] Baza użytkowników jest pusta.\n";
            } else {
                std::cout << std::left 
                        << std::setw(5) << "ID" 
                        << std::setw(20) << "Username" 
                        << std::setw(25) << "Haslo (Hash)" 
                        << std::setw(5) << "Wiek" 
                        << "\n------------------------------------------------------------\n";

                for (const auto& u : users) {
                    std::cout << std::left 
                            << std::setw(5) << u.getId() 
                            << std::setw(20) << u.getUsername()
                            << std::setw(25) << u.getPasswordHash() 
                            << std::setw(5) << u.getProfile().getAge() 
                            << std::endl;
                }
            }
            std::cout << "------------------------------------------------------------\n";
            std::cout << "1. Usuń użytkownika (po ID)\n";
            std::cout << "0. Wróć do menu głównego\n";
            std::cout << "Wybrana opcja -> ";
            
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Błąd: Wpisz liczbę!\n";
                continue;
            }

            switch (choice) {
                case 1: {
                    int idToDelete;
                    std::cout << "Podaj ID użytkownika do usunięcia: ";
                    std::cin >> idToDelete;
                    
                    if (userManager_.deleteAccount(idToDelete)) {
                        std::cout << "[SYSTEM] Sukces! Konto usunięte.\n";
                    } else {
                        std::cout << "[SYSTEM ERROR] Nie udało się usunąć konta.\n";
                    }
                    Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby przejść dalej...");
                    break;
                }
                case 0:
                    std::cout << "Wychodzenie z panelu admina...\n";
                    break;
                default:
                    std::cout << "Nieznana opcja.\n";
                    Utils::InputHandler::getLine("[Enter] Wciśnij 'Enter', aby przejść dalej...");
                    break;
            }
        }
    }

}