rem Run this in Developer Command Prompt.

rem Compile tests natively.
cl ^
    main.test.c ^
    cc65-test.c ^
    circular-buffer.test.c ^
    circular-buffer.c ^
    coord.test.c ^
    coord.c ^
    custom-asserts.c ^
    tile.c ^
    tile-to-index.c ^
    worm.c ^
    worm.test.c ^
    screen.c ^
    lz77-back-reference.c ^
    lz77-back-reference.test.c ^
    lz77.c ^
    lz77.test.c ^
    /Wall ^
    /W4 ^
    /wd4710 ^
    /wd4820 ^
    /wd4996 ^
    /wd4668 ^
    -o test.exe
if %errorlevel% neq 0 exit /b %errorlevel%

rem Run tests natively.
test.exe
if %errorlevel% neq 0 exit /b %errorlevel%

rem Compile tests for c64.
cl65 -O ^
    main.test.c ^
    cc65-test.c ^
    circular-buffer.test.c ^
    circular-buffer.c ^
    coord.test.c ^
    coord.c ^
    custom-asserts.c ^
    tile.c ^
    tile-to-index.c ^
    worm.c ^
    worm.test.c ^
    screen.c ^
    lz77-back-reference.c ^
    lz77-back-reference.test.c ^
    lz77.c ^
    lz77.test.c ^
    -o test.prg
if %errorlevel% neq 0 exit /b %errorlevel%

rem Run tests in c64 emulator.
x64sc -warp test.prg
