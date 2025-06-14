cmake_minimum_required(VERSION 3.29) 
project(BarbieFashionTycoon)         # project name

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# === Raylib ===
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib raygui)

FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG 4.0
)

add_executable(${PROJECT_NAME}
    source/main.cpp
    source/MainScreen.cpp
    source/Screen1.cpp
    source/screen2.cpp
    source/screen4.cpp
    source/GameManager.cpp
    source/play.cpp
    source/outfit.cpp
    source/shoes.cpp
    source/fashionShow.cpp
    source/finalfashionshow.cpp
    source/inventory.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

set(GENERATED_HEADERS_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_HEADERS_DIR})

file(COPY "${raygui_SOURCE_DIR}/src/raygui.h" DESTINATION "${GENERATED_HEADERS_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE ${GENERATED_HEADERS_DIR})

target_link_libraries(${PROJECT_NAME} raylib)

# === Copy assets/ folder (images, music, etc.) on build ===
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
