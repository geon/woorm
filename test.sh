#!/bin/bash

# Exit on error
set -e

# Compile tests natively.
clang \
    main.test.c \
    cc65-test.c \
    circular-buffer.test.c \
    circular-buffer.c \
    coord.test.c \
    coord.c \
    custom-asserts.c \
    tile.c \
    tile-to-index.c \
    worm.c \
    worm.test.c \
    screen.c \
    lz77-back-reference.c \
    lz77-back-reference.test.c \
    lz77.c \
    lz77.test.c \
    -o test.exe

# Run tests natively.
./test.exe

# Compile tests for c64.
export CC65_HOME="$HOME/code/cc65"
export CC65_INC="$CC65_HOME/includes"
export LD65_LIB="$CC65_HOME/lib"
export LD65_CFG="$CC65_HOME/cfg"
export PATH="$PATH:$CC65_HOME/bin"
cl65 -O \
    main.test.c \
    cc65-test.c \
    circular-buffer.test.c \
    circular-buffer.c \
    coord.test.c \
    coord.c \
    custom-asserts.c \
    tile.c \
    tile-to-index.c \
    worm.c \
    worm.test.c \
    screen.c \
    lz77-back-reference.c \
    lz77-back-reference.test.c \
    lz77.c \
    lz77.test.c \
    -o test.prg

# Run tests in c64 emulator.
export PATH="$PATH:/Applications/vice-arm64-gtk3-3.6.1/bin"
x64sc -warp test.prg
