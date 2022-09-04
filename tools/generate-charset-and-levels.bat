cl ^
    buffer.c ^
    ../lz77-back-reference.c ^
    lz77-back-reference.tools.c ^
    lz77.c ^
    level.c ^
    uncompressed-levels.c ^
    original-worm-charset.c ^
    generate-charset-and-levels.c ^
    ../tile.c ^
    charset-char.c ^
    charset.c ^
    partial-charset.c ^
    tile.legacy.c ^
    original-levels-charset.c ^
    -o generate-charset-and-levels.exe
if %errorlevel% neq 0 exit /b %errorlevel%

generate-charset-and-levels.exe
