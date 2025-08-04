cmake_minimum_required(VERSION 3.15)
project(NHF_Farm C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

set(SRC_FILES
        src/character.c
        src/crypto/base64.c
        src/crypto/vigenere.c
        src/game.c
        src/item.c
        src/main.c
        src/mainMenu.c
        src/map.c
        src/pauseMenu.c
        src/render.c
        src/saveManager.c
        src/settingsMenu.c
)

# Only use the resource file for Windows
if(WIN32)
    set(RESOURCE_FILE assets/app_icon.rc)
else()
    set(RESOURCE_FILE "")
endif()

add_executable(NHF_Farm ${SRC_FILES} ${RESOURCE_FILE})

if(WIN32)
    target_include_directories(NHF_Farm PRIVATE
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/lib/SDL2/include
            ${CMAKE_SOURCE_DIR}/lib/SDL2_image/include
            ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/include
    )
    target_link_directories(NHF_Farm PRIVATE
            ${CMAKE_SOURCE_DIR}/lib/SDL2/lib/x64
            ${CMAKE_SOURCE_DIR}/lib/SDL2_image/lib/x64
            ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/lib/x64
    )
    target_link_libraries(NHF_Farm
            SDL2.lib
            SDL2main.lib
            SDL2_image.lib
            SDL2_ttf.lib
    )
    add_custom_command(TARGET NHF_Farm POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/lib/SDL2/lib/x64/SDL2.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SDL2.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/lib/SDL2_image/lib/x64/SDL2_image.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SDL2_image.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/lib/x64/SDL2_ttf.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SDL2_ttf.dll
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    )
else()
    # Linux/WSL: Use system SDL2
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    target_include_directories(NHF_Farm PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${SDL2_IMAGE_INCLUDE_DIRS}
            ${SDL2_TTF_INCLUDE_DIRS}
            ${CMAKE_SOURCE_DIR}/src
    )
    target_link_libraries(NHF_Farm
            ${SDL2_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_TTF_LIBRARIES}
    )
endif()

# Preprocessor definitions
target_compile_definitions(NHF_Farm PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        _CONSOLE
        $<$<PLATFORM_ID:Windows>:WIN32>
)

# Compiler warnings (optional, recommended)
if(MSVC)
    target_compile_options(NHF_Farm PRIVATE /W3)
else()
    target_compile_options(NHF_Farm PRIVATE -Wall -Wextra)
endif()