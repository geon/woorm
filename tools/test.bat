cl ^
    ../cc65-test.c ^
    main.test.c ^
    charset-char.test.c ^
    charset-char.c ^
    charset.test.c ^
    charset.c ^
    partial-charset.test.c ^
    partial-charset.c ^
    tile.legacy.test.c ^
    tile.legacy.c ^
    buffer.test.c ^
    buffer.c ^
    lz77-back-reference.test.c ^
    lz77-back-reference.tools.c ^
    ../lz77-back-reference.c ^
    lz77.test.c ^
    lz77.c ^
    level.test.c ^
    level.c ^
    /Wall ^
    /W4 ^
    /wd4710 ^
    /wd4464 ^
    /wd4255 ^
    /wd4996 ^
    /wd4668 ^
    -o test.exe
if %errorlevel% neq 0 exit /b %errorlevel%

test.exe
