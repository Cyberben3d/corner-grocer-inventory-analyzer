# Build Guide - Corner Grocer Inventory Analyzer

This guide explains the compilation options available for the Corner Grocer Inventory Analyzer and best practices for GitHub integration.

## Compilation Options

### 1. Shell Script (`compile.sh`) - Recommended for Unix/Linux/macOS

**Features:**
- Cross-platform compatibility (Unix-like systems)
- Automatic compiler detection
- Clean build process
- Helpful error messages
- Progress indicators

**Usage:**
```bash
chmod +x compile.sh  # Make executable (first time only)
./compile.sh         # Compile the program
```

**Best for:** macOS, Linux, and other Unix-like systems

### 2. Batch Script (`compile.bat`) - Recommended for Windows

**Features:**
- Windows-specific compilation
- Automatic compiler detection
- Clean build process
- Helpful error messages
- Pause on completion for user review

**Usage:**
```cmd
compile.bat  # Compile the program
```

**Best for:** Windows systems with MinGW-w64 or WSL

### 3. Makefile - Recommended for Developers

**Features:**
- Standard build system
- Multiple targets (build, clean, docs, run)
- Dependency management
- Cross-platform compatibility
- Integration with development tools

**Usage:**
```bash
make        # Build the program
make run    # Build and run
make clean  # Clean build artifacts
make docs   # Generate documentation
make help   # Show all options
```

**Best for:** Developers familiar with make, CI/CD systems

### 4. Manual Compilation - For Advanced Users

**Features:**
- Direct control over compilation flags
- Custom optimization options
- Platform-specific tweaks

**Usage:**
```bash
g++ -std=c++11 -Wall -Wextra -pedantic -o main main.cpp
```

**Best for:** Advanced users who need custom compilation options

## GitHub Integration Best Practices

### 1. File Organization

```
CornerGrocerCode/
├── main.cpp                          # Source code
├── compile.sh                        # Unix compilation script
├── compile.bat                       # Windows compilation script
├── Makefile                          # Make-based build system
├── .github/workflows/                # GitHub Actions
│   ├── build.yml                    # Automated builds and testing
│   └── deploy-docs.yml              # Documentation generation and deployment
├── README.md                         # Main documentation
└── BUILD_GUIDE.md                   # This file
```

### 2. GitHub Actions Workflows

#### Build Workflow (`.github/workflows/build.yml`)
**Purpose:** Compilation and testing across multiple platforms
- **Automated testing** on multiple platforms (Ubuntu, macOS, Windows)
- **Multiple compiler support** (GCC, Clang)
- **Artifact uploads** for compiled binaries
- **Input file validation**

#### Documentation Workflow (`.github/workflows/deploy-docs.yml`)
**Purpose:** Documentation generation and deployment
- **Doxygen installation** and configuration
- **Documentation generation** from source code
- **GitHub Pages deployment** for online documentation
- **Automatic updates** when code changes

### 3. Documentation Strategy

**README.md** includes:
- Quick start instructions for all compilation methods
- Platform-specific installation guides
- Troubleshooting section
- Clear project structure

**BUILD_GUIDE.md** (this file) provides:
- Detailed explanation of each build method
- GitHub integration best practices
- Advanced usage scenarios

### 4. Version Control Considerations

**Included in Git:**
- ✅ Source code (`main.cpp`)
- ✅ Build scripts (`compile.sh`, `compile.bat`, `Makefile`)
- ✅ Configuration files (`Doxyfile`)
- ✅ Documentation templates
- ✅ GitHub Actions workflows
- ✅ Input data file (for testing)

**Excluded from Git (via .gitignore):**
- ❌ Compiled binaries (`main`, `main.exe`)
- ❌ Object files (`*.o`)
- ❌ Generated documentation (`docs/html/`)
- ❌ IDE-specific files
- ❌ OS-specific files

### 5. Release Strategy

**For GitHub Releases:**
1. **Source Code**: Always include the complete source
2. **Pre-compiled Binaries**: Upload compiled executables for major platforms
3. **Documentation**: Include generated HTML documentation
4. **Build Scripts**: Include all compilation scripts

**Release Assets Example:**
```
CornerGrocer-v1.0.0/
├── Source/
│   ├── main.cpp
│   ├── compile.sh
│   ├── compile.bat
│   ├── Makefile
│   └── Doxyfile
├── Binaries/
│   ├── corner-grocer-macos
│   ├── corner-grocer-linux
│   └── corner-grocer-windows.exe
└── Documentation/
    └── html/
```

## Platform-Specific Considerations

### macOS
- **Compiler**: Xcode Command Line Tools (clang)
- **Script**: `compile.sh` or `make`
- **Installation**: `xcode-select --install`

### Linux
- **Compiler**: GCC or Clang
- **Script**: `compile.sh` or `make`
- **Installation**: `sudo apt-get install g++` (Ubuntu/Debian)

### Windows
- **Compiler**: MinGW-w64 or MSVC
- **Script**: `compile.bat` or WSL with `compile.sh`
- **Installation**: Download MinGW-w64 or use WSL

## Troubleshooting

### Common Issues and Solutions

**"Permission denied" on compile.sh**
```bash
chmod +x compile.sh
```

**"g++ command not found"**
- macOS: `xcode-select --install`
- Ubuntu: `sudo apt-get install g++`
- Windows: Install MinGW-w64

**"make command not found"**
- Ubuntu: `sudo apt-get install make`
- macOS: Comes with Xcode Command Line Tools

**Compilation warnings/errors**
- Ensure C++11 support: `-std=c++11`
- Check for missing dependencies
- Verify source code syntax

## Best Practices Summary

1. **Provide Multiple Build Options**: Different users prefer different approaches
2. **Include Clear Documentation**: Both in README and dedicated build guide
3. **Automate Testing**: Use GitHub Actions for continuous integration
4. **Cross-Platform Support**: Ensure scripts work on major platforms
5. **Error Handling**: Provide helpful error messages and solutions
6. **Version Control**: Include build scripts, exclude generated files
7. **Release Strategy**: Provide both source and pre-compiled binaries
8. **Separation of Concerns**: Keep build and documentation workflows separate

## Contributing

When contributing to this project:
1. Test all build methods before submitting
2. Update documentation if build process changes
3. Ensure GitHub Actions continue to pass
4. Follow the existing code style and structure

---

*This guide is part of the Corner Grocer Inventory Analyzer project by Benjamin Orona, Chada Tech.* 