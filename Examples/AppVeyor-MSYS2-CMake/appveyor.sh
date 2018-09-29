#!/bin/bash

cd "$(dirname "$0")"

pacman -Syuu --noconfirm --force
pacman --noconfirm -S --needed mingw-w64-x86_64-toolchain
pacman --noconfirm -S --needed mingw-w64-x86_64-cmake
pacman --noconfirm -S --needed mingw-w64-x86_64-ntldd

mkdir build/ ; cd build/
cmake -G"MSYS Makefiles" ../
make V=1

ntldd `which cmake`
