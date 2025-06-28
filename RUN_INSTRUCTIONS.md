# Corner Grocer Inventory Analyzer - Quick Start

## 🚀 Running the Program

### Option 1: Direct Execution (Recommended)

**On macOS/Linux:**
```bash
./main
```

**On Windows:**
```cmd
main.exe
```

### Option 2: Using Compilation Scripts

**On macOS/Linux:**
```bash
chmod +x compile.sh
./compile.sh
./main
```

**On Windows:**
```cmd
compile.bat
main.exe
```

### Option 3: Using Makefile

```bash
make run
```

### Option 4: Manual Compilation

```bash
g++ -std=c++11 -Wall -Wextra -pedantic -o main main.cpp
./main
```

## 📁 Files Included

- `main` / `main.exe` - The compiled program
- `main.cpp` - Complete source code
- `CS210_Project_Three_Input_File.txt` - Input data file (required)
- `README.md` - Full documentation
- `RUN_INSTRUCTIONS.md` - This quick start guide
- `compile.sh` - Unix/Linux/macOS compilation script
- `compile.bat` - Windows compilation script
- `Makefile` - Make-based build system

## ⚠️ Requirements

- The input file `CS210_Project_Three_Input_File.txt` must be in the same directory as the executable
- Terminal/Command Prompt with proper Unicode support for best display
- C++ compiler (g++, clang, or MSVC) if you want to recompile from source

## 🎯 What the Program Does

This program analyzes grocery store inventory data and provides:
- Item search functionality
- Numerical display of all items
- Visual histogram display with color coding
- Automatic data persistence

## 📖 Full Documentation

For complete documentation, visit: https://cyberben3d.github.io/corner-grocer-inventory-analyzer

---

*Developed by Benjamin Orona, Chada Tech* 