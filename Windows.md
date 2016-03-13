# dynamicLinker instructions for Windows users

## Prerequisites
You will need [MSYS2](https://msys2.github.io/) and will have to type all commands in MSYS2 window.

## Update MSYS2
`update core`, restart MSYS2, then `pacman -Syu`

## Install dependencies

    pacman -Sy
    pacman -S mingw-w64-x86_64-gcc make git
    echo "PATH+=:/mingw64/bin:" >> ~/.bashrc
    source ~/.bashrc

## Build

    git clone https://github.com/Marqin/dynamicLinker.git
    cd dynamicLinker
    make CC=gcc CXX=g++

It will produce `libdynamicLinker.a` that you can statically link to your app.

## Testing

If you want to test dynamicLinker you can run:

    make CC=gcc CXX=g++ test-windows
