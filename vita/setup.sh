#!/bin/bash

install() {
  mkdir build
  cp "$1"/* build/
  cd build
  vita-makepkg
  local tarFile=$(find "." -type f -name "*.tar.xz" -print)
  vdpm $tarFile
  cd ..
  rm -rf build
}

cd vitabuilds
install "box2d"
install "enet"
install "GahoodSON"
install "sdl2"
install "sdl2_image"
install "sdl2_mixer"
install "sdl2_ttf"

