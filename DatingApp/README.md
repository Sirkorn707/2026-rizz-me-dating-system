# 💘Rizz.me Dating System💘

> **Terminalowa aplikacja randkowa napisana w C++. Znajdź swoją drugą połówkę w konsoli!**

## O projekcie

**Rizz.me** to symulator systemu randkowego działający w pełni w terminalu. Projekt powstał w celu nauki zaawansowanych struktur obiektowego C++, obsługi baz danych oraz architektury aplikacji. Aplikacja pozwala na tworzenie profili, "swipowanie" potencjalnych partnerów oraz czatowanie z dopasowanymi użytkownikami. 

## Główne funkcjonalności

* **System Użytkowników:**
    * Rejestracja i logowanie (haszowane hasła).
    * Walidacja wieku (18+) i płci.
    * Edycja profilu (Bio, Hobby, Wiek).
* **System Dopasowań (Matching):**
    * Algorytm obliczania zgodności (%) na podstawie wspólnych zainteresowań.
    * Mechanizm Swipe (Tak/Nie).
* **System Wiadomości:**
    * Prywatne czaty z dopasowanymi osobami.
    * Historia rozmów zapisywana w bazie danych.
* **Panel Administratora:**
    * Zarządzanie użytkownikami (usuwanie).
    * Podgląd statystyk bazy danych.

## Uruchamianie aplikacji na Windowsie

### Wymagania
* Kompilator C++ wspierający standard C++17 (np. GCC, MinGW).
* Biblioteka **SQLite3**.

### Instalacja i Kompilacja (Windows)

1.  **Sklonuj repozytorium:**
    ```bash
    git clone https://github.com/Sirkorn707/2026-rizz-me-dating-system.git
    ```
2.  **Przejdź do folderu projektu, utwórz nowy folder do budowania:**
    ```bash
    cd 2026-rizz-me-dating-system
    cd DatingApp
    mkdir build
    cd build
    ```
3.  **Skompiluj projekt:**
    ```bash
    cmake ..
    ```
4.  **Uruchom aplikację:**
    ```bash
    ./DatingApp.exe
    ```

## Uruchamianie na Linuxie

1.  **Pobierz repozytorium i zainstaluj biblioteki:**
    ```bash
    git clone https://github.com/Sirkorn707/2026-rizz-me-dating-system.git
    cd DatingApp
    sudo apt update
    sudo apt install g++ cmake make libsqlite3-dev
    ```

2.  **Stwórz nowy folder do budowania i skompiluj:**
    ```bash
    mkdir build_linux
    cd build_linux
    cmake ..
    make
    ```

3.  **Uruchom aplikację:**
    ```bash
    ./DatingApp
    ```

## Struktura Projektu

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
