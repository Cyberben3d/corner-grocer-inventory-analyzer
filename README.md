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

## Project Reflection

### Project Summary and Problem Statement

**What problem was this project solving?**
This project addresses the need for efficient inventory analysis in retail environments. The Corner Grocer Inventory Analyzer processes daily purchase data to provide insights into item popularity and informs the need to keep certain items in stock. The application transforms a raw purchase list into a searchable database and provides either a numerical or visual summary in the form of a histogram.

**Key challenges addressed:**
- Processing potentially large volumes of purchase data efficiently
- Providing an easy-to-read visualization format
- Displaying a progress bar during file processing in a terminal environment
- Creating a user-friendly interface for non-technical users
- Handling errors, exceptions, and erroneous user input in a graceful way

### What Was Done Particularly Well

**Technical Excellence:**
- **Cross-platform compatibility** with proper handling of Windows, macOS, and Linux differences
- **Object-oriented design** with clear separation of concerns using classes like `Utils`, `Database`, and `InventoryAnalyzer`
- **Comprehensive error handling** with custom exception classes and graceful failure with useful error messages
- **Professional build system** with multiple compilation options (scripts, Makefile, manual) for Windows, macOS, and Linux

**User Experience:**
- **Visual feedback** including progress bars, colored output, and ASCII art
- **Case-insensitive search** with ability to handle Apples, APPLES, apples, or aPPleS
- **Color Key** (for both numerical and histogram) indicating item popularity via common heat-map colors

**Development Practices:**
- **Extensive documentation** using Doxygen with complete API reference
- **Automated testing** through GitHub Actions across multiple platforms
- **Professional packaging** with complete release workflows
- **Version control** with proper tagging strategies and automated release generation for all supported platforms

### Areas for Enhancement

**Performance Improvements:**
- **Memory optimization**: Implement smart pointers and move semantics for better memory management in case of very large files
- **Algorithm efficiency**: Use more efficient data structures for large datasets (e.g., unordered_map for O(1) lookups)
- **I/O optimization**: Implement buffered reading for very large input files

**Security Enhancements:**
- **Input validation**: Add more robust sanitization of user inputs and file contents
- **Error logging**: Add comprehensive logging system for debugging and security auditing

**Feature Extensions:**
- **Database integration**: Support for SQLite, Firebase, or other databases for larger datasets
- **Export capabilities**: Add support for CSV, JSON, and other export formats
- **Real-time updates**: Implement file watching for automatic updates when input files change

### Most Challenging Code Sections

**Cross-Platform Console Handling:**
The most challenging aspect was implementing consistent console behavior across Windows, macOS, and Linux. The solution involved creating platform-specific preprocessor directives and conditional compilation blocks. I overcame this by researching platform differences and implementing a unified `Utils` class that abstracts platform-specific details as much as possible. Color handling was particularly challenging to get consistent colors between Windows and MacOS/Linux. Even clearing the screen has to be platform specific.

**Unicode and Character Display:**
Handling Unicode characters (like the histogram blocks █ abd ASCII art characters) across different terminals and operating systems was particularly challenging. I solved this by implementing UTF-8 encoding and platform-specific console configuration as well as using the /utf-8 option for Visual Studio when compiling on Windows.

**GitHub Actions Workflow:**
Creating automated build and release workflows that work across multiple platforms required significant troubleshooting. The main challenges were shell compatibility (PowerShell vs bash) and proper job dependencies. I overcame these by implementing platform-specific steps and careful job orchestration.

**Tools and Resources Added:**
- GitHub Actions for CI/CD automation
- Doxygen for documentation generation
- Cross-platform build scripts and Makefiles
- Professional release management workflows

### Transferable Skills

**Programming Fundamentals:**
- **Object-oriented design principles** applicable to any language
- **Error handling and exception management** patterns
- **Algorithm design and data structure selection**
- **Memory management and resource handling**

**Software Engineering:**
- **Version control and collaborative development** using Git
- **Automated testing and continuous integration** practices
- **Documentation and code commenting** standards
- **Build system design** and dependency management

**Professional Development:**
- **Cross-platform development** and compatibility considerations
- **User interface design** and user experience principles
- **Project organization** and file structure best practices
- **Release management** and deployment strategies

### Maintainability, Readability, and Adaptability

**Code Organization:**
- **Modular design** with separate classes for different responsibilities
- **Consistent naming conventions** and coding standards
- **Comprehensive comments** explaining complex logic and design decisions
- **Logical file structure** with clear separation of concerns

**Maintainability Features:**
- **Configuration-driven design** with easily modifiable constants
- **Extensible class hierarchy** allowing for easy feature additions
- **Comprehensive error handling** making debugging easier
- **Platform abstraction layers** reducing maintenance overhead

**Adaptability Strategies:**
- **Template-based design** allowing for easy customization
- **Comprehensive documentation** enabling other developers to understand and modify the code

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