cl ^
    compress-levels.c ^
    buffer.c ^
    ../lz77-back-reference.c ^
    lz77-back-reference.tools.c ^
    lz77.c ^
    level.c ^
    uncompressed-levels.c ^
    -o compress-levels.exe
if %errorlevel% neq 0 exit /b %errorlevel%

compress-levels.exe
