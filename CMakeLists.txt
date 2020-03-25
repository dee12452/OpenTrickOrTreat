cmake_minimum_required(VERSION 3.7)

project(OpenTrickOrTreat)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/map ${CMAKE_SOURCE_DIR}/src/util ${CMAKE_SOURCE_DIR}/src/sprite ${CMAKE_SOURCE_DIR}/src/screen ${CMAKE_SOURCE_DIR}/include)

add_executable(OpenTrickOrTreat ${SOURCE_FILES})
target_link_libraries(OpenTrickOrTreat ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib/libGahoodSON.a)
