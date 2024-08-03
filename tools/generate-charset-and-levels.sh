#!/bin/bash

set -e

clang \
    buffer.c \
    ../lz77-back-reference.c \
    lz77-back-reference.tools.c \
    lz77.c \
    level.c \
    uncompressed-levels.c \
    original-worm-charset.c \
    generate-charset-and-levels.c \
    ../tile.c \
    charset-char.c \
    charset.c \
    partial-charset.c \
    tile.legacy.c \
    original-levels-charset.c \
    original-levels-charset-b.c \
    level-charset-geon.c \
    -o generate-charset-and-levels.exe

./generate-charset-and-levels.exe
