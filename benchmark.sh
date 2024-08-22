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
    circular-buffer.c \
    coord.c \
    main.benchmark.c \
    tile.c \
    tile.benchmark.c \
    worm.c \
    worm.benchmark.c \
    screen.c \
    cc65-benchmark.c \
    tile-to-index.c \
    -o benchmark.prg

# Run benchmarks in c64 emulator.
export PATH="$PATH:/Applications/vice-arm64-gtk3-3.6.1/bin"
x64sc -warp benchmark.prg
