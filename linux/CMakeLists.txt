cmake_minimum_required(VERSION 3.9)

project(OpenTrickOrTreat)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/../src/*.cpp)
file(COPY ${CMAKE_SOURCE_DIR}/../assets DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(${CMAKE_SOURCE_DIR}/../third-party/SDL ${CMAKE_BINARY_DIR}/third-party/SDL)
add_subdirectory(${CMAKE_SOURCE_DIR}/../third-party/SDL_image ${CMAKE_BINARY_DIR}/third-party/SDL_image)
add_subdirectory(${CMAKE_SOURCE_DIR}/../third-party/SDL_ttf ${CMAKE_BINARY_DIR}/third-party/SDL_ttf)
add_subdirectory(${CMAKE_SOURCE_DIR}/../third-party/SDL_mixer ${CMAKE_BINARY_DIR}/third-party/SDL_mixer)
add_subdirectory(${CMAKE_SOURCE_DIR}/../third-party/GahoodSON ${CMAKE_BINARY_DIR}/third-party/GahoodSON)
add_subdirectory(${CMAKE_SOURCE_DIR}/../third-party/box2d ${CMAKE_BINARY_DIR}/third-party/box2d)
add_subdirectory(${CMAKE_SOURCE_DIR}/../third-party/enet ${CMAKE_BINARY_DIR}/third-party/enet)

include_directories(${CMAKE_SOURCE_DIR}/../include)

add_executable(OpenTrickOrTreat ${SOURCE_FILES})
target_link_libraries(OpenTrickOrTreat SDL2 SDL2_image SDL2_ttf SDL2_mixer GahoodSON box2d enet)
target_include_directories(OpenTrickOrTreat PRIVATE
        ${CMAKE_SOURCE_DIR}/../third-party/SDL/include
        ${CMAKE_SOURCE_DIR}/../third-party/SDL_image/include
        ${CMAKE_SOURCE_DIR}/../third-party/SDL_ttf/include
        ${CMAKE_SOURCE_DIR}/../third-party/SDL_mixer/include
        ${CMAKE_SOURCE_DIR}/../third-party/GahoodSON/include
        ${CMAKE_SOURCE_DIR}/../third-party/box2d/include
        ${CMAKE_SOURCE_DIR}/../third-party/enet/include
)
