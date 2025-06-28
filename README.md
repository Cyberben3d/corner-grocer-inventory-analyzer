# Corner Grocer Inventory Analyzer

\mainpage

A C++ application for analyzing grocery store inventory data, developed by Benjamin Orona for Chada Tech.

## Features

- **Item Search**: Search for specific items by name with case-insensitive matching
- **Numerical Display**: View all items with their purchase counts in a clean numerical format
- **Histogram Display**: Visualize item frequencies using colored histograms
- **Data Persistence**: Automatically saves processed data to `frequency.dat`
- **Cross-Platform**: Works on Windows, macOS, and Linux with proper console handling

## Documentation

📚 **[View Full Documentation](https://cyberben3d.github.io/corner-grocer-inventory-analyzer)**

The documentation includes:
- Complete API reference
- Class diagrams and inheritance hierarchies
- Function documentation with parameters and return values
- Code examples and usage patterns

## Building and Running

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- Doxygen (for documentation generation)

### Quick Start

#### Option 1: Using Compilation Scripts (Recommended)

**On macOS/Linux:**
```bash
# Make the script executable (first time only)
chmod +x compile.sh

# Compile the application
./compile.sh

# Run the application
./main
```

**On Windows:**
```cmd
# Compile the application
compile.bat

# Run the application
main.exe
```

#### Option 2: Using Makefile

```bash
# Build the application
make

# Or build and run in one command
make run

# Clean build artifacts
make clean

# Generate documentation
make docs

# See all available options
make help
```

#### Option 3: Manual Compilation

```bash
# Compile the application
g++ -std=c++11 -Wall -Wextra -pedantic -o main main.cpp

# Run the application
./main
```

### Compiler Installation

**macOS:**
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Or use make to install dependencies
make install-macos
```

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install g++

# Or use make to install dependencies
make install-ubuntu
```

**CentOS/RHEL:**
```bash
sudo yum install gcc-c++

# Or use make to install dependencies
make install-centos
```

**Windows:**
- Install MinGW-w64 from https://www.mingw-w64.org/
- Or use WSL (Windows Subsystem for Linux) and install Ubuntu from Microsoft Store

### Documentation Generation
```bash
# Generate documentation
doxygen Doxyfile

# View documentation
open docs/html/index.html  # macOS
xdg-open docs/html/index.html  # Linux
start docs/html/index.html  # Windows

# Or use make
make docs
```

### Input File Format
The application expects an input file named `CS210_Project_Three_Input_File.txt` with one item per line:
```
Apple
Banana
Orange
Apple
```

### Output
- Console output with interactive menu system
- `frequency.dat` file with item counts
- HTML documentation in `docs/html/` directory

## Project Structure

```
CornerGrocerCode/
├── main.cpp                          # Main application source
├── compile.sh                        # Unix/Linux/macOS compilation script
├── compile.bat                       # Windows compilation script
├── Makefile                          # Make-based build system
├── Doxyfile                          # Doxygen configuration
├── CS210_Project_Three_Input_File.txt # Sample input data
├── docs/                             # Generated documentation
│   └── html/                         # HTML documentation files
└── .github/workflows/                # GitHub Actions for auto-deployment
    ├── deploy-docs.yml              # Documentation deployment workflow
    └── build.yml                    # Automated build and test workflow
```

## Development

This project uses modern C++ features and follows best practices:
- Object-oriented design with clear separation of concerns
- Comprehensive error handling and validation
- Cross-platform compatibility
- Extensive documentation with Doxygen

## Troubleshooting

### Common Issues

**"g++ command not found"**
- Install the C++ compiler for your platform (see Compiler Installation above)
- Ensure the compiler is in your system PATH

**"Permission denied" on compile.sh**
- Run: `chmod +x compile.sh`

**"make command not found"**
- Install make: `sudo apt-get install make` (Ubuntu/Debian)
- On macOS, make comes with Xcode Command Line Tools

**Program crashes or doesn't start**
- Ensure `CS210_Project_Three_Input_File.txt` exists in the same directory
- Check that the input file is not empty and has proper formatting

**Unicode characters not displaying correctly (Windows)**
- The program automatically sets UTF-8 encoding on Windows
- If issues persist, run the program in a modern terminal (Windows Terminal recommended)

## License

Developed by Benjamin Orona for Chada Tech as part of CS-210 Programming Languages coursework. 