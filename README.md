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

### Build Instructions
```bash
# Compile the application
g++ -o main main.cpp

# Generate documentation
doxygen Doxyfile

# Run the application
./main
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
├── Doxyfile                          # Doxygen configuration
├── CS210_Project_Three_Input_File.txt # Sample input data
├── docs/                             # Generated documentation
│   └── html/                         # HTML documentation files
└── .github/workflows/                # GitHub Actions for auto-deployment
    └── deploy-docs.yml              # Documentation deployment workflow
```

## Development

This project uses modern C++ features and follows best practices:
- Object-oriented design with clear separation of concerns
- Comprehensive error handling and validation
- Cross-platform compatibility
- Extensive documentation with Doxygen

## License

Developed by Benjamin Orona for Chada Tech as part of CS-210 Programming Languages coursework. 