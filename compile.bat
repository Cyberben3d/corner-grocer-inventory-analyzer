@echo off
REM Corner Grocer Inventory Analyzer - Compilation Script
REM Author: Benjamin Orona, Chada Tech
REM Date: 6/20/2025
REM Class: CS-210 Programming Languages
REM Assignment: 7-3 Project Three

echo ==========================================
echo Corner Grocer Inventory Analyzer
echo Compilation Script
echo ==========================================
echo.

REM Check if g++ is available
g++ --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: g++ compiler not found!
    echo Please install g++ or ensure it's in your PATH.
    echo.
    echo You can install MinGW-w64 or use WSL for Linux tools.
    echo.
    echo For MinGW-w64:
    echo   1. Download from: https://www.mingw-w64.org/
    echo   2. Add the bin directory to your PATH
    echo.
    echo For WSL (Windows Subsystem for Linux):
    echo   1. Enable WSL in Windows Features
    echo   2. Install Ubuntu from Microsoft Store
    echo   3. Run: sudo apt-get install g++
    pause
    exit /b 1
)

echo ✓ g++ compiler found
echo.

REM Clean previous builds
echo Cleaning previous builds...
if exist main.exe del main.exe
if exist main del main
if exist *.o del *.o
echo ✓ Cleaned previous builds
echo.

REM Compile the program
echo Compiling main.cpp...
g++ -std=c++11 -Wall -Wextra -pedantic -o main.exe main.cpp

REM Check if compilation was successful
if %errorlevel% equ 0 (
    echo ✓ Compilation successful!
    echo.
    echo Executable created: main.exe
    echo.
    echo To run the program:
    echo   main.exe
    echo.
    echo Make sure CS210_Project_Three_Input_File.txt is in the same directory.
) else (
    echo ✗ Compilation failed!
    echo Please check the error messages above.
    pause
    exit /b 1
)

echo ==========================================
echo Compilation complete!
echo ==========================================
pause 