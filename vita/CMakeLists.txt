cmake_minimum_required(VERSION 3.9)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif()
endif()

project(OpenTrickOrTreat)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/../src/*.cpp)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "OpenTrickOrTreat")
set(VITA_TITLEID  "TRICTREAT")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

include_directories(
        ${CMAKE_SOURCE_DIR}/../include
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        box2d
        SDL2
        SDL2_image
        SDL2_ttf
        enet
        png
        jpeg
        turbojpeg
        webp
        zlibstatic
        freetype
        harfbuzz
        m
        pthread
        SceDisplay_stub
        SceCtrl_stub
        SceAudio_stub
        SceSysmodule_stub
        SceGxm_stub
        SceCommonDialog_stub
        SceAppMgr_stub
        SceTouch_stub
        SceHid_stub
        SceMotion_stub
        SceAudioIn_stub
        SceNet_stub
        SceNetCtl_stub
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
        VERSION ${VITA_VERSION}
        NAME ${VITA_APP_NAME}
        FILE ${CMAKE_SOURCE_DIR}/../assets/opensans.ttf assets/opensans.ttf
)
