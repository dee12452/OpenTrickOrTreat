cmake_minimum_required(VERSION 3.0.0)
project(OpenTrickOrTreat)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/map ${CMAKE_SOURCE_DIR}/src/util ${CMAKE_SOURCE_DIR}/src/sprite ${CMAKE_SOURCE_DIR}/src/screen ${CMAKE_SOURCE_DIR}/include)

add_executable(OpenTrickOrTreat ${SOURCE_FILES})
target_link_libraries(OpenTrickOrTreat ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/libGahoodSON.a)
