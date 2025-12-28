cmake_minimum_required(VERSION 3.10)
project(DatingApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SQLite3
find_package(SQLite3 REQUIRED)

# Find OpenSSL for hashing (opcjonalnie, możesz użyć bcrypt)
find_package(OpenSSL REQUIRED)

# Wszystkie pliki źródłowe
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")

add_executable(DatingApp ${SOURCES} ${HEADERS})

# Linkowanie
target_link_libraries(DatingApp 
    SQLite::SQLite3 
    OpenSSL::Crypto
)

# Ostrzeżenia
if(MSVC)
    target_compile_options(DatingApp PRIVATE /W3 /WX)
else()
    target_compile_options(DatingApp PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Include directories
target_include_directories(DatingApp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)