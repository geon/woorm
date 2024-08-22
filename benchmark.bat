rem Run this in Developer Command Prompt.

rem Compile benchmark for c64.
cl65 -O ^
    circular-buffer.c ^
    coord.c ^
    main.benchmark.c ^
    tile.c ^
    tile.benchmark.c ^
    worm.c ^
    worm.benchmark.c ^
    screen.c ^
    cc65-benchmark.c ^
    tile-to-index.c ^
    -o benchmark.prg
if %errorlevel% neq 0 exit /b %errorlevel%

rem Run in c64 emulator.
x64sc -warp benchmark.prg
