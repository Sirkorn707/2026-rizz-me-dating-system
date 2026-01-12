/*  FILE DESCRIPTION
    <---Rizz.me Dating System Application--->
    <Author: Krzysztof Ornacki, AD 2026>
    File: colors.h
    Description: Header file for the color definitions.
*/
#ifndef UTILS_COLORS_H
#define UTILS_COLORS_H

#include <string>

/* File information:
    All colors data taken from:
    https://gist.github.com/Kielx/2917687bc30f567d45e15a4577772b02 

    This file is not used in the current version of the application,
    but it is kept for potential future use in enhancing terminal output.
*/

namespace Utils {
    namespace Colors {
        const std::string RESET   = "\033[0m";
        const std::string RED     = "\033[31m";
        const std::string GREEN   = "\033[32m";
        const std::string YELLOW  = "\033[33m";
        const std::string BLUE    = "\033[34m";
        const std::string MAGENTA = "\033[35m";
        const std::string CYAN    = "\033[36m";
        const std::string BOLD    = "\033[1m";

        const std::string ICON_HEART = "❤️";
        const std::string ICON_USER  = "👤";
        const std::string ICON_CHECK = "✅";
        const std::string ICON_CROSS = "❌";
        const std::string ICON_FIRE  = "🔥";
        const std::string ICON_STAR  = "⭐";
    }
}

#endif 