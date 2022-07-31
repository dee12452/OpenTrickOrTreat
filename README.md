# OpenTrickOrTreat
An open source recreation of the cartoon network online flash game Operation T.R.I.C.K. Or T.R.E.A.T. written in C++ using SDL2.

## ARCHIVED
This project has been archived due to the lack of available resources (mainly audio and some fonts) to recreate the game fully.
As of now you can still play the game using a program called [Flashpoint](https://bluemaxima.org/flashpoint).

## Setup / Install

You'll need to make sure you have make, cmake, and SDL2 installed using your system's package manager.<br/>
`pacman -S make cmake sdl2 sdl2_image sdl2_ttf`


<br/>Next thing you'll need to to is run the setup script. This will install the necessary headers and static libraries from the third party submodules.<br/>
`./setup.sh`

<br/>Now you should be able to build the OpenTrickOrTeat binary using cmake.<br/>
`cmake . && make`

