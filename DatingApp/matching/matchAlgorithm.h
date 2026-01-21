/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: matchAlgorithm.h
    Description: Header file for the match algorithm implementation.
*/
#ifndef MATCHING_MATCHALGORITHM_H
#define MATCHING_MATCHALGORITHM_H

#include "../user/user.h"

namespace Matching {

    /* Class description: MatchAlgorithm
        EN: Class implementing my own matching algorithm between users.
        PL: Klasa implementująca autorski algorytm dopasowania między użytkownikami.

        Algorithm details:
            -> Max possible score: 100 points.
            -> Scoring based on shared interests and age difference.
            -> Up to 80 points for shared interests (20 points each, max 4 counted).
            -> Up to 20 points for age difference (0 years = 20 points, gradually decreasing to: 7 years = 0 points).
    */
    class MatchAlgorithm {
    public:

        /* Function description: calculateScore()
            EN: Static method to calculate match score (0-100).
            PL: Metoda statyczna obliczająca wynik dopasowania (0-100).
        */
        static int calculateScore(const User::User& user1, const User::User& user2);
    };

}

#endif