rem Compile tests for c64.
cl65 -O ^
    worm-charset.asm ^
    main.c ^
    circular-buffer.c ^
    worm.c ^
    coord.c ^
    tile.c ^
    tile-to-index.c ^
    screen.c ^
    level.c ^
    levels.c ^
    lz77.c ^
    screen-location-c64.c ^
    worms.c ^
    title-screen.c ^
    -DJOYSTICK_DRIVER=c64_ptvjoy_joy ^
    -C c64-c-gamedev.cfg ^
    -o woorm.prg
if %errorlevel% neq 0 exit /b %errorlevel%

rem Run tests in c64 emulator.
x64sc woorm.prg
