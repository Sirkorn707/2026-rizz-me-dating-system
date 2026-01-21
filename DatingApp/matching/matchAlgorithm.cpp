/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: matchAlgorithm.cpp
    Description: Implementation of the match algorithm.
*/
#include "matchAlgorithm.h"
#include <cmath> // Used functions: std::abs
#include <vector>
#include <string>

namespace Matching {

    int MatchAlgorithm::calculateScore(const User::User& user1, const User::User& user2) {
        // INTERESTS MATCHING (Max 80 pts).
        auto interests1 = user1.getProfile().getInterests();
        auto interests2 = user2.getProfile().getInterests();

        int matchesCount = 0;
        for (const auto& i1 : interests1) {
            for (const auto& i2 : interests2) {
                if (i1 == i2) {
                    matchesCount++;
                    break; // Code description: Match found, move to next interest from user1.
                }
            }
        }

        if (matchesCount > 4) matchesCount = 4;
        int hobbyScore = matchesCount * 20;

        // AGE DIFFERENCE (Max 20 pts).
        int age1 = user1.getProfile().getAge();
        int age2 = user2.getProfile().getAge();
        
        int diff = std::abs(age1 - age2);
        int ageScore = 0;

        if (diff <= 7) {
            /* Equation explained:
            -> According to our logic, we want a linear decrease from 20 to 0 points as the age difference goes from 0 to 7.
            -> When diff = 0, score = 20.
            -> When diff = 7, score = 0.
            -> Formula: (7 - diff) / 7.0 * 20.
            -> Example: diff 0 -> 1.0 * 20 = 20.
            -> Example: diff 3 -> 4/7 * 20 = 11.43 (rounded to 11).
            */
            double factor = (7.0 - diff) / 7.0;
            ageScore = static_cast<int>(20.0 * factor);
        }

        return hobbyScore + ageScore;
    }

}