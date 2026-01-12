/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: testData.h
    Description: Header file for the test data loading implementation.
*/
#ifndef UTILS_TESTDATA_H
#define UTILS_TESTDATA_H

#include "../user/UserManager.h"
#include "../security/PasswordManager.h"
#include "Colors.h"
#include <iostream>
#include <vector>
#include <string>

namespace Utils {

    /* Structure description: FakeProfile
        EN: Structure containing several user profiles for testing.
        PL: Struktura zawierająca kilka profili użytkowników do testów.
    */
    struct FakeProfile {
        std::string login;
        std::string rawPassword;
        int age;
        std::string description;
        User::Gender gender;
        std::vector<std::string> interests;
    };
        
    /* Function description: loadTestData
        EN: Loads test user data into the database if it's empty.
        PL: Ładuje testowe dane użytkowników do bazy, jeśli jest pusta.
    */
    void loadTestData(User::UserManager& userManager) {
        auto existingUsers = userManager.getAllUsers();
        if (!existingUsers.empty()) {
            return; 
        }

        std::vector<FakeProfile> fakeDb = {
            {"Bartek", "haslo123", 24, "Koduje w C++, szukam kogos do debugowania zycia.", User::Gender::Male, {"programowanie", "gry", "technologia"}},
            {"Ania", "haslo123", 22, "Studentka ASP. Maluje, rysuje i pije duzo kawy.", User::Gender::Female, {"sztuka", "kawa", "muzyka"}},
            {"Piotr", "haslo123", 28, "Silownia to moj drugi dom.", User::Gender::Male, {"silownia", "sport", "zdrowie"}},
            {"Ola", "haslo123", 25, "Bylam w 30 krajach. Nastepny cel: Japonia.", User::Gender::Female, {"podroze", "fotografia", "jezyki"}},
            {"Maja", "haslo123", 21, "Mole ksiazkowe laczmy sie! Fanatyczka fantasy.", User::Gender::Female, {"ksiazki", "fantasy", "filmy"}},
            {"Marek", "haslo123", 30, "Kocham szybkie samochody.", User::Gender::Male, {"motoryzacja", "f1", "mechanika"}},
            {"Zosia", "haslo123", 19, "Lubie imprezy i dobre jedzenie.", User::Gender::Female, {"imprezy", "taniec", "moda"}},
            {"Tomek", "haslo123", 20, "Gambling, Piwo.", User::Gender::Male, {"esport", "gry", "anime"}},
            {"Ewa", "haslo123", 26, "Gory, las i cisza. Szukam kogos na szlak.", User::Gender::Female, {"gory", "trekking", "natura"}},
            {"Michal", "haslo123", 29, "Gotuje lepiej niz Twoja babcia.", User::Gender::Male, {"gotowanie", "wino", "kuchnia wloska"}},
            {"Julia", "haslo123", 23, "Taniec to moje zycie. Salsa i Bachata.", User::Gender::Female, {"taniec", "muzyka", "fitness"}},
            {"Robert", "haslo123", 35, "Wlasna firma, duzo pracuje.", User::Gender::Male, {"biznes", "ekonomia", "inwestycje"}},
            {"Karolina", "haslo123", 24, "Weganizm i joga. Peace & Love.", User::Gender::Female, {"joga", "weganizm", "ekologia"}},
            {"Lukasz", "haslo123", 27, "Lapie chwile w obiektywie.", User::Gender::Male, {"fotografia", "film", "sztuka"}},
            {"Monika", "haslo123", 25, "Studentka medycyny.", User::Gender::Female, {"medycyna", "seriale", "nauka"}},
            {"Krzysiek", "haslo123", 32, "Stary rock i gitara elektryczna.", User::Gender::Male, {"muzyka", "koncerty", "gitara"}},
            {"Natalia", "haslo123", 21, "Siatkowka i plaza.", User::Gender::Female, {"sport", "plaza", "siatkowka"}},
            {"Adam", "haslo123", 29, "Historia to moja pasja.", User::Gender::Male, {"historia", "muzea", "ksiazki"}},
            {"Pati", "haslo123", 22, "Mam 3 psy. Musisz lubic zwierzeta!", User::Gender::Female, {"psy", "zwierzeta", "spacery"}},
            {"Mikolaj", "haslo123", 26, "Kinomaniak.", User::Gender::Male, {"kino", "netflix", "rezyseria"}},
            {"Kamil", "haslo123", 26, "Fullstack developer. Szukam kogos, kto zrozumie moje zarty o CSS.", User::Gender::Male, {"programowanie", "tech", "rower"}},
            {"Weronika", "haslo123", 22, "Studentka psychologii. Analizuje ludzi dla sportu i maluje obrazy.", User::Gender::Female, {"sztuka", "psychologia", "muzea"}},
            {"Darek", "haslo123", 45, "Spokojny facet. W weekendy tylko ryby i dzialka.", User::Gender::Male, {"wedkarstwo", "natura", "grill"}},
            {"Alex", "haslo123", 23, "Wolna dusza. Nie lubie etykietek. Kocham podroze autostopem.", User::Gender::Other, {"podroze", "lgbt", "wolnosc"}},
            {"Daisy", "haslo123", 28, "Trenerka personalna. Zrobie z Ciebie bestie na silowni!", User::Gender::Female, {"fitness", "silownia", "zdrowie"}},
            {"Gor", "haslo123", 19, "Glownie LoL i CS:GO. Szukam duo do grania i zycia.", User::Gender::Male, {"gry", "esport", "twitch"}},
            {"Basia", "haslo123", 52, "Uwielbiam piec ciasta i zajmowac sie ogrodem. Szukam przyjazni.", User::Gender::Female, {"ogrod", "kuchnia", "koty"}},
            {"Krzysztof", "haslo123", 34, "Motocykle to moja pasja. LwG!", User::Gender::Male, {"motocykle", "mechanika", "zuzel"}},
            {"Jan", "haslo123", 25, "Kawa alternatywna, winyle i kino niszowe.", User::Gender::Male, {"kawa", "muzyka", "kino"}},
            {"Sandra", "haslo123", 21, "Moda, zakupy i Instagram. Szukam kogos, kto robi dobre zdjecia.", User::Gender::Female, {"moda", "instagram", "zakupy"}},
            {"Tomasz", "haslo123", 38, "Blockchain, krypto i gielda. Buduje imperium.", User::Gender::Male, {"finanse", "krypto", "biznes"}},
            {"Emilia", "haslo123", 24, "Bibliotekarka z powolania. Harry Potter to zycie.", User::Gender::Female, {"ksiazki", "fantasy", "pisanie"}},
            {"Seba", "haslo123", 21, "Sporty walki i silka. Szukam konkretnej dziewczyny.", User::Gender::Male, {"mma", "boks", "sport"}},
            {"Zuza", "haslo123", 26, "Aktywistka, weganka. Ratujmy planete razem!", User::Gender::Female, {"ekologia", "weganizm", "zwierzeta"}},
            {"Piotr", "haslo123", 31, "Gram na perkusji w kapeli. Szukam muzy.", User::Gender::Male, {"muzyka", "rock", "koncerty"}},
            {"CichyMichal", "haslo123", 29, "Introwertyk. Lubie deszcz, szachy i spokojne wieczory.", User::Gender::Male, {"szachy", "nauka", "programowanie"}},
            {"Wojtek", "haslo123", 40, "Zwiedzilem 50 krajow. Szukam towarzyszki na kolejna wyprawe.", User::Gender::Male, {"podroze", "gory", "fotografia"}},
            {"AnimeWiki", "haslo123", 18, "Cosplay i konwenty. Uwielbiam Japonie!", User::Gender::Female, {"anime", "manga", "japonia"}},
            {"Mario", "haslo123", 33, "Szef kuchni. Przez zoladek do serca.", User::Gender::Male, {"gotowanie", "jedzenie", "wino"}},
            {"Artur", "haslo123", 21, "Szukam towarzyszki do picia piwa.", User::Gender::Male, {"piwo", "elektronika", "programowanie"}},
            {"Renata", "haslo123", 48, "Każdy weekend na szlaku. Tatry to mój drugi dom.", User::Gender::Female, {"gory", "trekking", "narty"}}
        };

        for (const auto& data : fakeDb) {
            // Code description: hash password, user creation, and registration.
            std::string securePass = Security::PasswordManager::hashPassword(data.rawPassword);
            User::Profile profile(data.age, data.description, data.gender, data.interests);
            User::User newUser(-1, data.login, securePass, profile);
            userManager.registerUser(newUser);
        }

        std::cout << Colors::GREEN << Colors::ICON_CHECK << " Zaladowano " << fakeDb.size() << " uzytkownikow do bazy." << Colors::RESET << std::endl;
        std::cout << "Domyslne haslo dla wszystkich: " << Colors::BOLD << "haslo123" << Colors::RESET << std::endl;
    }
}

#endif