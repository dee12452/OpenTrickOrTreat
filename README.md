# OpenTrickOrTreat
An open source recreation of the cartoon network online flash game Operation T.R.I.C.K. Or T.R.E.A.T. written in C++ using SDL2.

## Setup / Install

You'll need to make sure you have make, cmake, and SDL2 installed using your system's package manager.<br/>
`pacman -S make cmake sdl2 sdl2_image sdl2_ttf`


<br/>Next thing you'll need to to is run the setup script. This will install the necessary headers and static libraries from the third party submodules.<br/>
`./setup.sh`

<br/>Now you should be able to build the OpenTrickOrTeat binary using cmake.<br/>
`cmake . && make`

