# 💘 Rizz.me Dating System

> **Terminalowa aplikacja randkowa napisana w C++. Znajdź swoją drugą połówkę w konsoli!**

![C++](https://img.shields.io/badge/C++-17-blue.svg?style=flat&logo=c%2B%2B)

## 📖 O projekcie

**Rizz.me** to symulator systemu randkowego działający w pełni w terminalu. Projekt powstał w celu nauki zaawansowanych struktur obiektowego C++, obsługi baz danych oraz architektury aplikacji. Aplikacja pozwala na tworzenie profili, "swipowanie" potencjalnych partnerów oraz czatowanie z dopasowanymi użytkownikami. 

## ✨ Główne funkcjonalności

* **🔐 System Użytkowników:**
    * Rejestracja i logowanie (haszowane hasła).
    * Walidacja wieku (18+) i płci.
    * Edycja profilu (Bio, Hobby, Wiek).
* **❤️ System Dopasowań (Matching):**
    * Algorytm obliczania zgodności (%) na podstawie wspólnych zainteresowań.
    * Mechanizm Swipe (Tak/Nie).
* **💬 System Wiadomości:**
    * Prywatne czaty z dopasowanymi osobami.
    * Historia rozmów zapisywana w bazie danych.
* **🛠️ Panel Administratora:**
    * Zarządzanie użytkownikami (usuwanie).
    * Podgląd statystyk bazy danych.

## 🚀 Uruchamianie aplikacji

### Wymagania
* Kompilator C++ wspierający standard C++17 (np. GCC, MinGW, MSVC).
* Biblioteka **SQLite3**.
* Preferowany system operacyjny Windows 10/11

### Instalacja i Kompilacja

1.  Sklonuj repozytorium:
    ```bash
    git clone [https://github.com/Sirkorn707/2026-rizz-me-dating-system.git](https://github.com/Sirkorn707/2026-rizz-me-dating-system.git)
    ```
2.  Przejdź do folderu projektu:
    ```bash
    cd DatingApp
    ```
3.  Skompiluj projekt:
    ```bash
    cmake ..
    ```
4.  Uruchom aplikację:
    ```bash
    ./DatingApp.exe
    ```

## 🏗️ Struktura Projektu

```text
DatingApp/
├── core/
│   ├── sqlite3.cpp
│   ├── sqlite3.h
├── matching/
│   ├── matchAlgorithm.cpp
│   ├── matchAlgorithm.h
│   ├── message.h
│   ├── messageManager.cpp
│   └── messageManager.h
├── security/
│   ├── passwordManager.h
├── storage/
│   ├── database.cpp
│   ├── database.h
├── ui/
│   ├── displayManager.cpp
│   ├── displayManager.h
│   ├── terminalUI.cpp
│   ├── terminalUI.h
├── user/
│   ├── profile.cpp
│   ├── profile.h
│   ├── user.cpp
│   ├── user.h
│   ├── userManager.cpp
│   └── userManager.h
├── utils/
│   ├── colors.h
│   ├── helperFunctions.h
│   ├── inputHandler.cpp
│   ├── inputHandler.h
│   └── testData.h
├── CMakeLists.txt
├── main.cpp
└── README.md
