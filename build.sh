#!/bin/bash

# Exit on error
set -e

# Compile for c64.
export CC65_HOME="$HOME/code/cc65"
export CC65_INC="$CC65_HOME/includes"
export LD65_LIB="$CC65_HOME/lib"
export LD65_CFG="$CC65_HOME/cfg"
export PATH="$PATH:$CC65_HOME/bin"
cl65 -O \
    worm-charset.asm \
    main.c \
    circular-buffer.c \
    worm.c \
    coord.c \
    tile.c \
    tile-to-index.c \
    screen.c \
    level.c \
    levels.c \
    lz77.c \
    screen-location-c64.c \
    -DJOYSTICK_DRIVER=c64_ptvjoy_joy \
    -C c64-c-gamedev.cfg \
    -o woorm.prg

# Run in c64 emulator.
export PATH="$PATH:/Applications/vice-arm64-gtk3-3.6.1/bin"
x64sc woorm.prg
