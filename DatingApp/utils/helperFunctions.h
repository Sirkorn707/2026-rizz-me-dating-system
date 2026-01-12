/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: helperFunctions.h
    Description: Header file for the helper functions implementation.
*/
#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <string>
#include <vector>
#include <sstream> // Used classes: std::stringstream, std::istringstream
#include <thread> // Used function: std::this_thread::sleep_for
#include <chrono> // Used function: std::chrono::milliseconds

namespace Utils {

    /* Class description: HelperFunctions
        EN: Class providing various helper functions for string manipulation and other utilities.
        PL: Klasa dostarczająca różne funkcje pomocnicze do manipulacji napisami i inne narzędzia.
    */
    class HelperFunctions {
    public:
        /* Function description: joinVector()
            EN: Static method to join a vector of strings into a single string with a specified delimiter.
            PL: Metoda statyczna łącząca wektor napisów w jeden napis z określonym separatorem.
        */
        static std::string joinVector(const std::vector<std::string>& vec, char delimiter) {
            std::stringstream ss;
            for (size_t i = 0; i < vec.size(); ++i) {
                ss << vec[i];
                if (i < vec.size() - 1) {
                    ss << delimiter;
                }
            }
            return ss.str();
        }

        /* Function description: splitString()
            EN: Static method to split a string into a vector of strings based on a specified delimiter.
            PL: Metoda statyczna dzieląca napis na wektor napisów na podstawie określonego separatora.
        */
        static std::vector<std::string> splitString(const std::string& s, char delimiter) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream tokenStream(s);
            while (std::getline(tokenStream, token, delimiter)) {
                tokens.push_back(token);
            }
            return tokens;
        }

        /* Function description: sanitize()
            EN: Static method to sanitize a string for safe database insertion by escaping single quotes.
            PL: Metoda statyczna oczyszczająca napis do bezpiecznego wstawiania do bazy danych poprzez usuwanie pojedynczych apostrofów.
        */
        static std::string sanitize(const std::string& input) {
            std::string safe = input;
            size_t pos = 0;
            
            // Szukamy znaku ' w pętli
            while ((pos = safe.find("'", pos)) != std::string::npos) {
                // Zamieniamy 1 znak na pozycji pos na string "''"
                safe.replace(pos, 1, "''");
                // Przesuwamy się o 2 miejsca dalej (bo dodaliśmy znak), żeby nie zapętlić się
                pos += 2;
            }
            return safe;
        }
    
        /* Function description: sleep()
            EN: Static method to pause execution for a specified number of milliseconds.
            PL: Metoda statyczna wstrzymująca wykonanie na określoną liczbę milisekund.
        */
        static void sleep(int milliseconds) {
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        }
    };

}

#endif