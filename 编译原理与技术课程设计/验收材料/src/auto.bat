@echo off
setlocal enabledelayedexpansion

echo the pascal compiler is running
set LOG_FILE=compilation.log
echo the running time stamp is : %date% %time% > %LOG_FILE%

rem is tools exist?
where flex >nul 2>nul
if %errorlevel% neq 0 (
    echo can not find flex
    echo can not find flex >> %LOG_FILE%
    goto :error
)

where bison >nul 2>nul
if %errorlevel% neq 0 (
    echo can not find Bison
    echo can not find Bison >> %LOG_FILE%
    goto :error
)

where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo can not find g++
    echo can not find g++ >> %LOG_FILE%
    goto :error
)

rem ִexecute the step of compiling
echo 1. Run the Flex Generative Lexicon...
echo 1. Run the Flex Generative Lexicon... >> %LOG_FILE%
flex NEW_PASCC.l >> %LOG_FILE% 2>&1
if %errorlevel% neq 0 (
    echo Error: Flex Execution failed
    type %LOG_FILE%
    goto :error
)

echo 2. Run Bison to generate a parser...
echo 2. Run Bison to generate a parser... >> %LOG_FILE%
bison -d NEW_PASCC.y >> %LOG_FILE% 2>&1
if %errorlevel% neq 0 (
    echo Error: Bison Execution Failed!
    type %LOG_FILE%
    goto :error
)

echo 3. Compile the final program with g++.
echo 3. Compile the final program with g++. >> %LOG_FILE%
echo last_merge
g++ lex.yy.c NEW_PASCC.tab.c ast.cpp main.cc -std=c++17 -o pascc -w >> %LOG_FILE% 2>&1
if %errorlevel% neq 0 (
    echo Error: g Failed to compile!
    type %LOG_FILE%
    goto :error
)

echo Compilation successful! Executable :pascc.exe
echo Compilation successful! Executable :pascc.exe >> %LOG_FILE%
exit /b 0

:error
echo An error occurred during the compilation process! See %LOG_FILE% for details.
exit /b 1