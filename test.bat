rem Run this in Developer Command Prompt.

rem Compile tests natively.
cl ^
    demo.test.c ^
    cc65-test.c
if %errorlevel% neq 0 exit /b %errorlevel%

rem Run tests natively.
demo.test.exe
if %errorlevel% neq 0 exit /b %errorlevel%

rem Compile tests for c64.
cl65 -O ^
    demo.test.c ^
    cc65-test.c ^
    -o demo.test.prg
if %errorlevel% neq 0 exit /b %errorlevel%

rem Run tests in c64 emulator.
x64sc demo.test.prg
