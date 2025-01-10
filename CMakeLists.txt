cmake_minimum_required(VERSION 3.10)

# Project neve
project(NHF_Farm LANGUAGES C)

# C szabvány
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# SDL2 keresése
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Forrásfájlok hozzáadása
file(GLOB_RECURSE SOURCES "src/*.c")

# Az executable létrehozása
add_executable(${PROJECT_NAME} ${SOURCES})

# SDL2 linkelése
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(NHF_Farm PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
