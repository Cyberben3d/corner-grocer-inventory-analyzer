# Corner Grocer Inventory Analyzer - Makefile
# Author: Benjamin Orona, Chada Tech
# Date: 6/20/2025
# Class: CS-210 Programming Languages
# Assignment: 7-3 Project Three

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
TARGET = main
SOURCE = main.cpp

# Default target
all: $(TARGET)

# Compile the main executable
$(TARGET): $(SOURCE)
	@echo "Compiling $(SOURCE)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)
	@echo "✓ Compilation successful!"
	@echo "Executable created: $(TARGET)"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(TARGET) $(TARGET).exe *.o
	@echo "✓ Cleaned build artifacts"

# Install dependencies (macOS)
install-macos:
	@echo "Installing dependencies for macOS..."
	xcode-select --install || echo "Xcode Command Line Tools already installed or installation failed"

# Install dependencies (Ubuntu/Debian)
install-ubuntu:
	@echo "Installing dependencies for Ubuntu/Debian..."
	sudo apt-get update
	sudo apt-get install -y g++ doxygen

# Install dependencies (CentOS/RHEL)
install-centos:
	@echo "Installing dependencies for CentOS/RHEL..."
	sudo yum install -y gcc-c++ doxygen

# Generate documentation
docs:
	@echo "Generating documentation..."
	doxygen Doxyfile
	@echo "✓ Documentation generated in docs/html/"

# Run the program
run: $(TARGET)
	@echo "Running $(TARGET)..."
	./$(TARGET)

# Check if input file exists
check-input:
	@if [ ! -f "CS210_Project_Three_Input_File.txt" ]; then \
		echo "✗ Error: CS210_Project_Three_Input_File.txt not found!"; \
		echo "Please ensure the input file exists in the current directory."; \
		exit 1; \
	else \
		echo "✓ Input file found"; \
	fi

# Full build with checks
build: check-input $(TARGET)
	@echo "✓ Build complete and ready to run"

# Help target
help:
	@echo "Corner Grocer Inventory Analyzer - Makefile"
	@echo "=========================================="
	@echo ""
	@echo "Available targets:"
	@echo "  all          - Build the executable (default)"
	@echo "  build        - Build with input file validation"
	@echo "  clean        - Remove build artifacts"
	@echo "  docs         - Generate documentation"
	@echo "  run          - Build and run the program"
	@echo "  check-input  - Verify input file exists"
	@echo ""
	@echo "Installation targets:"
	@echo "  install-macos  - Install dependencies on macOS"
	@echo "  install-ubuntu - Install dependencies on Ubuntu/Debian"
	@echo "  install-centos - Install dependencies on CentOS/RHEL"
	@echo ""
	@echo "Usage examples:"
	@echo "  make              # Build the program"
	@echo "  make run          # Build and run"
	@echo "  make clean        # Clean build files"
	@echo "  make docs         # Generate documentation"

.PHONY: all clean install-macos install-ubuntu install-centos docs run check-input build help 