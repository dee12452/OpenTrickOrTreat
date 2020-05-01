# OpenTrickOrTreat

An open source recreation of the cartoon network online flash game T.R.I.C.K. O.R. T.R.E.A.T.

## Setup / Install

You'll need to make sure you have cmake installed onto your system.
`sudo pacman -S cmake`

You'll also need `make` but that should be part of the base development packages on your distribution.
`$ sudo pacman -S base-devel`

The final packages you should need are sdl2, sdl2_image, and sdl2_ttf.
`$ sudo pacman -S sdl2 sdl2_image sdl2_ttf`

Last thing you'll need to do is include GahoodSON as part of the project. GahoodSON is a C library that parses JSON objects into C structs.
```
$ git clone git@github.com:dee12452/GahoodSON.git
$ cd GahoodSON
$ cmake . && make
$ cd .. && mkdir -p lib include/GahoodSON
$ cp GahoodSON/src/*.h include/GahoodSON
$ cp GahoodSON/libGahoodSON.a lib/
$ rm -rf GahoodSON
```

Now you should be able to build and run the game.
```
$ cmake . && make
$ ./OpenTrickOrTreat
```
