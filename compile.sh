#!/bin/bash

# Corner Grocer Inventory Analyzer - Compilation Script
# Author: Benjamin Orona, Chada Tech
# Date: 6/20/2025
# Class: CS-210 Programming Languages
# Assignment: 7-3 Project Three

echo "=========================================="
echo "Corner Grocer Inventory Analyzer"
echo "Compilation Script"
echo "=========================================="
echo ""

# Check if g++ is available
if ! command -v g++ &> /dev/null; then
    echo "ERROR: g++ compiler not found!"
    echo "Please install g++ or ensure it's in your PATH."
    echo ""
    echo "On macOS, you can install it with:"
    echo "  xcode-select --install"
    echo ""
    echo "On Ubuntu/Debian:"
    echo "  sudo apt-get install g++"
    echo ""
    echo "On CentOS/RHEL:"
    echo "  sudo yum install gcc-c++"
    exit 1
fi

echo "✓ g++ compiler found"
echo ""

# Clean previous builds
echo "Cleaning previous builds..."
rm -f main main.exe *.o
echo "✓ Cleaned previous builds"
echo ""

# Compile the program
echo "Compiling main.cpp..."
g++ -std=c++11 -Wall -Wextra -pedantic -o main main.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo ""
    echo "Executable created: main"
    echo ""
    echo "To run the program:"
    echo "  ./main"
    echo ""
    echo "Make sure CS210_Project_Three_Input_File.txt is in the same directory."
else
    echo "✗ Compilation failed!"
    echo "Please check the error messages above."
    exit 1
fi

echo "=========================================="
echo "Compilation complete!"
echo "==========================================" 