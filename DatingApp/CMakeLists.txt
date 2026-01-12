# --------------------------------------------------------
# <---Rizz.me Dating System Application--->
# <Author: Krzysztof Ornacki, AD 2026>
# <CMake Build Configuration>
# --------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

project(DatingApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --------------------------------------------------------
# SOURCE FILES BELOW:
# --------------------------------------------------------
add_executable(DatingApp 
    main.cpp
    
    # Core
    core/sqlite3.c
    
    # Storage
    storage/database.cpp
    
    # User 
    user/user.cpp
    user/userManager.cpp
    user/profile.cpp
    
    # Matching
    matching/messageManager.cpp
    matching/matchAlgorithm.cpp

    # UI
    ui/terminalUI.cpp
    ui/displayManager.cpp

    # Utils
    utils/inputHandler.cpp
)

# FOR LINUX & MACOS SYSTEMS
if(UNIX)
    target_link_libraries(DatingApp dl pthread)
endif()