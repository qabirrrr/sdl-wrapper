cmake_minimum_required(VERSION 3.15)
project(SDLpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BASE_PATH "C:/SDL2++/Base")

# Library
add_library(SDL2++ STATIC source/SDL++.cpp)
target_include_directories(SDL2++ PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${BASE_PATH}/include
)
link_directories(
    ${BASE_PATH}/lib
)
set_target_properties(SDL2++ PROPERTIES VERSION ${PROJECT_VERSION} ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

# Optional: link directories if needed for library dependencies
link_directories(${BASE_PATH}/lib)
