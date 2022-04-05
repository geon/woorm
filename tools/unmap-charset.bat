cl ^
    original-worm-charset.c ^
    unmap-charset.c ^
    ../tile.c ^
    charset-char.c ^
    charset.c ^
    partial-charset.c ^
    tile.legacy.c ^
    -o unmap-charset.exe
if %errorlevel% neq 0 exit /b %errorlevel%

unmap-charset.exe
