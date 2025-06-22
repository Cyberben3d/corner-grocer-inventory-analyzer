/**
 * main.cpp
 *
 * Author: Benjamin Orona, Chada Tech
 * Client: Corner Grocer
 * Date: 6/20/2025
 * Class: CS-210 Programming Languages
 * Assignment: 7-3 Project Three
 *
 * Purpose: Inventory analyzer
 * This program allows users to analyze the inventory of a store.
 * The program will read a file containing purchases for the day.
 * The program will then display the number of each item sold
 * using different display options. The program will also write
 * the results to a file.
 *
 * Input file: CS210_Project_Three_Input_File.txt
 * Input example:
 * Apple
 * Banana
 * Orange
 * Apple
 *
 * Output file: frequency.dat
 * Output example:
 * Apple 2
 * Banana 1
 * Orange 1
 *
 * Usage: ./main
 */

// --- Preprocessor Directives ---
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

// Windows specific preprocessor directives
#ifdef _WIN32
#include <windows.h>
#endif

// --- Class Definitions ---

/**
 * Utility class for the inventory analyzer
 */
class Utils {
public:
    /**
     * Clears the console screen in a cross-platform way.
     */
    static void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }

    /**
     * Sets the console text color
     *
     * @param t_color the color to set
     * @throws std::invalid_argument if the color is invalid
     */
    static void setConsoleTextColor(const std::string& t_color) {
    #ifdef _WIN32
        // Windows color map
        std::map<std::string, int> colorMap = {
            {"green", FOREGROUND_GREEN | FOREGROUND_INTENSITY},
            {"red", FOREGROUND_RED | FOREGROUND_INTENSITY},
            {"yellow", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY},
            {"blue", FOREGROUND_BLUE | FOREGROUND_INTENSITY},
            {"magenta", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY},
            {"cyan", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY},
            {"gray", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE},
            {"white", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY}
        };

        // Validate the color
        if (colorMap.find(t_color) == colorMap.end()) {
            throw std::invalid_argument("Invalid color: " + t_color);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorMap[t_color]);
    #else
        // Linux, macOS, color map
        std::map<std::string, std::string> colorMap = {
            {"green", "\033[92m"},
            {"red", "\033[91m"},
            {"yellow", "\033[93m"},
            {"blue", "\033[94m"},
            {"magenta", "\033[95m"},
            {"cyan", "\033[96m"},
            {"gray", "\033[90m"},
            {"white", "\033[97m"}
        };

        // Validate the color
        if (colorMap.find(t_color) == colorMap.end()) {
            throw std::invalid_argument("Invalid color: " + t_color);
        }
        std::cout << colorMap[t_color];
    #endif
    }

    /**
     * Clears the input buffer.
     */
    static void clearInputBuffer() {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(10000, '\n'); // Discard characters up to newline
    }

    /**
     * Waits for the user to press Enter.
     */
    static void waitForEnter() {
        std::cout << "Press Enter to continue...";
        std::string dummy;
        std::getline(std::cin, dummy); // Safely consume the Enter press
    }

    /**
    * Removes leading and trailing whitespace from a string.
    * Whitespace characters are: space, tab, carriage return, and newline.
    *
    * @param t_str the string to trim
    * @return the trimmed string
    */
    static std::string trim(const std::string& t_str) {
        const std::string whitespace = " \t\r\n";
        size_t start = t_str.find_first_not_of(whitespace);

        // If the string is empty or contains only whitespace, return an empty string
        if (start == std::string::npos) {
            return "";
        }
        size_t end = t_str.find_last_not_of(whitespace);
        return t_str.substr(start, end - start + 1);
    }

    /**
    * Opens an input file and checks if it exists.
    *
    * @param t_fileName the name of the file to open
    * @param t_fileStream the file stream to open
    * @return true if the file was opened successfully, false otherwise
    */
    static bool tryOpenInputFile(const std::string& t_fileName, std::ifstream& t_fileStream) {
        std::cout << "Opening " << t_fileName << " for input...";
        t_fileStream.open(t_fileName);
        if (!t_fileStream.is_open()) {
            std::cout << "ERROR" << std::endl << "Please make sure the file exists in the same directory as the program." << std::endl;
            return false;
        }
        std::cout << "OK" << std::endl;
        return true;
    }

    /**
    * Opens an output file and checks if it exists and if the program has permission to create it.
    *
    * @param t_fileName the name of the file to open
    * @param t_fileStream the file stream to open
    * @return true if the file was opened successfully, false otherwise
    */
    static bool tryOpenOutputFile(const std::string& t_fileName, std::ofstream& t_fileStream) {
        std::cout << "Opening " << t_fileName << " for output...";
        t_fileStream.open(t_fileName);
        if (!t_fileStream.is_open()) {
            std::cout << "ERROR" << std::endl << "Please make sure the program has permission to create the file in the same directory as the program." << std::endl;
            return false;
        }
        std::cout << "OK" << std::endl;
        return true;
    }

    /**
     * Gets the display length of a string (number of visible characters).
     * This is different from string.length() which returns bytes.
     * 
     * @param t_str the string to measure
     * @return the number of visible characters
     */
    static size_t getDisplayLength(const std::string& t_str) {
        size_t len = 0;
        for (size_t i = 0; i < t_str.length(); i++) {
            if ((t_str[i] & 0xC0) != 0x80) {  // Skip continuation bytes
                len++;
            }
        }
        return len;
    }

    /**
     * Centers a string within a given width.
     *
     * @param t_str the string to center
     * @param t_width the width of the output
     * @param t_paddingChar the character to use for padding
     * @param t_startChar the character to use for the start of the string
     * @param t_endChar the character to use for the end of the string
     * @return the centered string, the original string if it is longer than the width
     */
    static std::string centerString(const std::string& t_str, unsigned int t_width, std::string t_paddingChar = " ", std::string t_startChar = "", std::string t_endChar = "") {
        // Get display lengths (visible characters)
        size_t strLen = getDisplayLength(t_str);
        size_t startLen = getDisplayLength(t_startChar);
        size_t endLen = getDisplayLength(t_endChar);
        
        // Validate the string is not longer than the width
        if (strLen + startLen + endLen >= t_width) {
            return t_str;
        }
        
        // Calculate the padding
        size_t padding = t_width - strLen - startLen - endLen;
        size_t padLeft = padding / 2;
        size_t padRight = padding - padLeft;
        return t_startChar + repeatString(t_paddingChar, padLeft) + t_str + repeatString(t_paddingChar, padRight) + t_endChar;
    }

    /**
     * Centers two strings within a given width.
     *
     * @param t_str_left the left string to center
     * @param t_str_right the right string to center
     * @param t_width the width of the output
     * @param t_separator the separator to use between the two strings (optional, default is " ")
     * @return the centered strings
     */
    static std::string centerStrings(const std::string t_str_left, const std::string t_str_right, unsigned int t_width, std::string t_separator = " ") {
        int centerPoint = t_width / 2;

        // Create the left side of the string and position the right side of the string
        std::string leftSide;
        leftSide = std::string(centerPoint - getDisplayLength(t_str_left), ' ') + t_str_left;
        return leftSide + t_separator + t_str_right;
    }

    /**
     * Gets and validates integer input from the user.
     *
     * @param t_prompt the prompt to display to the user
     * @param t_errorMessage the error message to display if the input is invalid
     * @param t_minValue the minimum value the input can be (optional, default is 1)
     * @param t_maxValue the maximum value the input can be (optional, default is max int)
     * @return the integer input
     */
    static int getIntegerInput(const std::string& t_prompt, const std::string& t_errorMessage, int t_minValue = 1, int t_maxValue = 2147483647) {
        std::string input;
        while (true) {
            std::cout << t_prompt;
            std::getline(std::cin, input);
            
            // Check if input is empty or contains non-digit characters (allowing minus sign at start)
            if (input.empty() || 
                (input[0] != '-' && input.find_first_not_of("0123456789") != std::string::npos) ||
                (input[0] == '-' && input.length() > 1 && input.substr(1).find_first_not_of("0123456789") != std::string::npos)) {
                std::cout << t_errorMessage << std::endl;
                continue;
            }
            
            // Convert to integer and validate
            try {
                int value = std::stoi(input);
                if (value < t_minValue || value > t_maxValue) {
                    std::cout << t_errorMessage << std::endl;
                    continue;
                }
                return value;
            } catch (const std::exception&) {
                std::cout << t_errorMessage << std::endl;
            }
        }
    }

    /**
    * Prints a menu with numbered options.
    *
    * @param t_title the title of the menu
    * @param t_strings the array of choices
    * @param t_width the width of each line
    */
    static void printMenu(const std::string& t_title, const std::vector<std::string>& t_strings, unsigned int t_width) {
        std::string itemNum;
        std::string menuText;
        size_t spacesNeeded;

        // Print the title and top border
        std::cout << std::endl;
        std::cout << Utils::centerString(" " + t_title + " ", t_width, "═", "╔", "╗") << std::endl;
        std::cout << Utils::centerString("", t_width, " ", "║", "║") << std::endl;
        for (unsigned int i = 0; i < t_strings.size(); ++i) {
            // Prepare the menu line
            itemNum = std::to_string(i + 1);
            menuText = std::string("║ ") + itemNum + " - " + t_strings[i];
            spacesNeeded = t_width - Utils::getDisplayLength(menuText) - 1;

            // Print the menu line
            std::cout << menuText << std::string(spacesNeeded, ' ') << "║" << std::endl;
        }
        std::cout << Utils::centerString("", t_width, " ", "║", "║") << std::endl;

        // Print the bottom border
        std::cout << Utils::centerString("", t_width, "═", "╚", "╝") << std::endl;
    }

    /**
    * Gets menu choice 1 through maxChoice, inclusive.
    *
    * @param t_maxChoice the maximum choice index, must be greater than 0
    * @throws std::invalid_argument if t_maxChoice is 0
    * @return the first legal choice input, could be 1 through t_maxChoice, inclusive
    */
    static unsigned int getMenuChoice(unsigned int t_maxChoice) {
        if (t_maxChoice == 0) {
            throw std::invalid_argument("t_maxChoice must be greater than 0");
        }
        
        int maxChoice = static_cast<int>(t_maxChoice);
        int choice = Utils::getIntegerInput("Enter your choice (1-" + std::to_string(maxChoice) + "): ", "Invalid choice", 1, maxChoice);
        return static_cast<unsigned int>(choice);
    }

    /**
     * Creates a string of repeated characters using a string input for unicode support.
     * 
     * @param t_str the string to repeat
     * @param t_count number of times to repeat
     * @return string of repeated characters
     */
    static std::string repeatString(const std::string& t_str, int t_count) {
        std::string result;
        for (int i = 0; i < t_count; ++i) {
            result += t_str;
        }
        return result;
    }

    /**
     * Creates a progress bar with a given width and percentage.
     * 
     * @param t_width the width of the progress bar
     * @param t_percentage the percentage to display
     * @return the progress bar
     */
    static std::string createProgressBar(int t_width, double t_percent, std::string t_fillChar = "█", std::string t_emptyChar = "░") {
        std::string progressBar = "";
        int filledWidth = static_cast<int>(t_width * t_percent);
        int emptyWidth = t_width - filledWidth;

        progressBar += repeatString(t_fillChar, filledWidth);
        progressBar += repeatString(t_emptyChar, emptyWidth);
        progressBar += " " + std::to_string(static_cast<int>(t_percent * 100)) + "%";
        return progressBar;
    }

    /**
     * Prints progress bar based on line count with delay so user can see progress.
     *
     * @param t_lineCount the line count to print the progress bar for
     * @param t_currentLine the current line to print the progress bar for
     * @param t_width the width of the progress bar
     */
    static void printProgressBar(int t_lineCount, int t_currentLine, int t_width = 40) {
        if (t_lineCount <= 0) {
            return;
        }

        // Calculate and show progress with delay so user can see progress
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        double progress = static_cast<double>(t_currentLine) / t_lineCount;
        std::cout << Utils::createProgressBar(t_width, progress) << " " << t_currentLine << " of " << t_lineCount << "\r";
        std::cout.flush();
    }
};

/**
 * Database class that stores item counts and provides methods to search and display the data.
 */
class Database {
public:
    class DatabaseError : public std::runtime_error {
    public:
        explicit DatabaseError(const std::string& message) : std::runtime_error(message) {}
    };

private:
    std::map<std::string, int> m_itemCounts;
    int m_maxItemCount = 0;

    /**
     * Gets the line count of a file.
     *
     * @param t_inputFileStream the file stream to get the line count of
     * @return the line count of the file
     */
    int getLineCount(std::ifstream& t_inputFileStream) {
        int lineCount = 0;
        std::string line;
        while (std::getline(t_inputFileStream, line)) {
            if (line.empty()) {
                continue;
            }
            lineCount++;
        }

        // Reset the file pointer to the beginning
        t_inputFileStream.clear();
        t_inputFileStream.seekg(0, std::ios::beg);

        return lineCount;
    }

public:
    /**
     * Builds the database from the input file.
     *
     * @throws DatabaseError if the database cannot be built
     */
    void buildDatabaseFromFile(const std::string& t_inputFileName) {
        Utils::setConsoleTextColor("blue");

        // Open the input file
        std::ifstream inputFile;
        if (!Utils::tryOpenInputFile(t_inputFileName, inputFile)) {
            throw DatabaseError("Failed to open input file: " + t_inputFileName);
        }

        int lineCount = getLineCount(inputFile);

        // Check if the file is empty
        if (lineCount == 0) {
            throw DatabaseError("Input file is empty");
        }

        // Process the file line by line and store the item counts and show progress
        std::cout << "Reading input file" << " (" << lineCount << " lines)" << std::endl;
        std::string item;
        int currentLine = 0;
        while (inputFile >> item) {
            item = Utils::trim(item);
            if (item.empty()) {
                continue;
            }

            // Update the item count
            m_itemCounts[item]++;
            if (m_itemCounts[item] > m_maxItemCount) {
                m_maxItemCount = m_itemCounts[item];
            }

            currentLine++;
            Utils::printProgressBar(lineCount, currentLine);
        }
        std::cout << std::endl;
        inputFile.close();
    }

    /**
     * Write database backup to file.
     * 
     * @throws DatabaseError if the database cannot be written
     */
    void writeDatabaseBackup(const std::string& t_outputFileName) {
        Utils::setConsoleTextColor("yellow");

        // Open the output file
        std::ofstream outputFile;
        if (!Utils::tryOpenOutputFile(t_outputFileName, outputFile)) {
            throw DatabaseError("Failed to open output file: " + t_outputFileName);
        }

        // Write the database to the output file line by line and show progress
        std::cout << "Writing database backup" << " (" << m_itemCounts.size() << " lines)" << std::endl;
        int currentLine = 0;
        int lineCount = m_itemCounts.size();
        for (const auto& item : m_itemCounts) {
            outputFile << item.first << " " << item.second << std::endl;

            currentLine++;
            Utils::printProgressBar(lineCount, currentLine);
        }
        std::cout << std::endl;
        outputFile.close();
    }

    /**
     * Tries to get the count of an item.
     *
     * @param t_item the item to get the count of
     * @param t_count the count of the item
     * @return true if the count was found, false otherwise
     */
    bool tryGetItemCount(const std::string& t_item, int& t_count) {
        // Trim and validate the item
        std::string item = Utils::trim(t_item);
        if (item.empty()) {
            return false;
        }

        // Try to get the item with the key as entered (case-sensitive)
        auto it = m_itemCounts.find(item);
        if (it != m_itemCounts.end()) {
            t_count = it->second;
            return true;
        } else {
            // Try capitalizing the first letter of the item (peas -> Peas) (case-insensitive)
            item[0] = std::toupper(item[0]);
            it = m_itemCounts.find(item);
            if (it != m_itemCounts.end()) {
                t_count = it->second;
                return true;
            }
        }
        return false;
    }

    /**
     * Gets the item counts.
     *
     * @return the item counts
     */
    std::map<std::string, int> getItemCounts() {
        return m_itemCounts;
    }

    /**
     * Gets the max item count.
     *
     * @return the max item count
     */
    int getMaxItemCount() {
        return m_maxItemCount;
    }
};

/**
 * Inventory Analyzer class serves as the program controller.
 */
class InventoryAnalyzer {
private:
    std::string m_inputFileName = "CS210_Project_Three_Input_File.txt";
    std::string m_outputFileName = "frequency.dat";
    int m_displayWidth = 80;
    std::string m_uiColor = "cyan";
    Database m_database;
    std::vector<std::string> m_mainMenuOptions = {
        "Search for Item by Name",
        "Display Count of All Items (Numerical)",
        "Display Count of All Items (Histogram)",
        "Exit"
    };
    // define histogram colors as heatmap
    std::vector<std::string> m_heatMapColors = {
        "red",
        "yellow",
        "green",
        "blue",
    };

    /**
     * Prints ASCII Art Logo Part 1
     */
     void printLogoPart1() {
        std::cout << "    ░░░░░░░░░░░                                                                 " << std::endl;
        std::cout << "   ▒▒▓▓▓▓▓▓▓▓▒░                                                                 " << std::endl;
        std::cout << "  ▒▓▓▓▓▒▒▒▒▒▒▒░  ░▒▓▓▓▓▓▓▓▓░░ ░▒▓▓▒░▒▓▒░▒▓▓▓▒▒▒▓▓▓▓▒░  ░░▒▓▓▓▓▓▓▒░  ░▒▓▓▒▒▓▓▒░  " << std::endl;
        std::cout << "  ▒▓▓▓▒        ░▒▓▓▓▒▒▒▒▒▓▓▓▓░░▒▓▓▓▓▒▒▒░▒▓▓▓▓▓▒▒▒▓▓▓▓░░▒▓▓▓▒▒▒▒▒▓▒░ ░▒▓▓▓▓▒▒░░  " << std::endl;
        std::cout << "  ▒▓▓▓▒        ░▒▓▓▒░    ▒▓▓▓░░▒▓▓▒░    ▒▓▓▓░░  ░▒▓▓▓░░▒▓▓▒░░░░▒▓▓▒ ░▒▓▓▒░      " << std::endl;
        std::cout << "  ▒▓▓▓▒        ░▒▓▓▒░    ▒▓▓▓░░▒▓▓▒░    ▒▓▓▓░░   ▒▓▓▓░░▒▓▓▓▓▓▓▓▓▓▒░ ░▒▓▓▒░      " << std::endl;
        std::cout << "  ▒▓▓▓▓▒░▒▒▓▓▒░░▒▓▓▓░░░░░▒▓▓▓░░▒▓▓▒░    ▒▓▓▓░░   ▒▓▓▓░░▒▓▓▒░   ░░░░░░▒▓▓▒░      " << std::endl;
        std::cout << "  ░▒▓▓▓▓▓▓▓▓▓▒░░▒▓▓▓▓▓▓▓▓▓▓▓░ ░▒▓▓▒░    ▒▓▓▓░░   ▒▓▓▓░░░▓▓▓▓▓▓▓▓▓▓▒░░▒▓▓▒░      " << std::endl;
        std::cout << "    ░▒▒▒▒▒░░     ░░▒▒▒▒▒▒░░   ░░▒▒▒░    ░▒▒▒░░   ▒▒▒▒░  ░░▒▒▒▒▒░░░  ░▒▒▒░░      " << std::endl;
     }

    /**
     * Prints ASCII Art Logo Part 2
     */
     void printLogoPart2() {
        std::cout << "    ░▒▒▒▒▒▒▒▒▒░                                                                 " << std::endl;
        std::cout << "  ░▒▒▒▒▒▒▒▒▒▒▒░  ░░░░░ ░░░░  ░░░░░░░░░      ░░░░░░░░░   ░░░░░░░░   ░░░░░░░░░░   " << std::endl;
        std::cout << "  ░▒▒▒▒          ░▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒░ ░▒▒▒▒▒▒▒▒▒▒░ ░▒▒▒▒▒▒▒▒▒▒░ ░▒▒▒▒▒▒▒▒░   " << std::endl;
        std::cout << "  ░▒▒▒▒    ░░░░░ ░▒▒▒▒░░░░░▒▒▒▒░░░░░▒▒▒▒░░▒▒▒▒░░░░░░░ ▒▒▒▒░  ░░▒▒▒░░▒▒▒▒░░░░░   " << std::endl;
        std::cout << "  ░▒▒▒▒    ░▒▒▒░ ░▒▒▒▒░   ░▒▒▒▒    ░▒▒▒▒░░▒▒▒░░       ▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒░       " << std::endl;
        std::cout << "  ░▒▒▒▒░   ░▒▒▒░ ░▒▒▒▒░   ░▒▒▒▒    ░▒▒▒▒░░▒▒▒░░       ▒▒▒▒▒░░░░░░░░░▒▒▒▒░       " << std::endl;
        std::cout << "  ░▒▒▒▒▒▒▒▒▒▒▒▒░ ░▒▒▒▒░   ░▒▒▒▒▒▒▒▒▒▒▒▒░░░▒▒▒▒▒▒▒▒▒▒▒ ░▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒░       " << std::endl;
        std::cout << "   ░▒▒▒▒▒▒▒▒▒▒▒░ ░▒▒▒░░    ░▒▒▒▒▒▒▒▒▒▒░   ░▒▒▒▒▒▒▒▒░░ ░░▒▒▒▒▒▒▒▒▒░░░▒▒▒▒░       " << std::endl;
     }     

     /**
      * Print ASCII Art Chada Tech Logo
      */
     void printChadaTechLogo() {
        std::cout << "                                                     ░                          " << std::endl;
        std::cout << "                                                    ░░                          " << std::endl;
        std::cout << "                                                         ▒▒                     " << std::endl;
        std::cout << "                                                      ▒░        ░▒░             " << std::endl;
        std::cout << "                   ░▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░▒▒▒░        ░                  " << std::endl;
        std::cout << "                 ░█████████████████████████████░░▒▒▒░ ░▒▒▒   ░░                 " << std::endl;
        std::cout << "                ░███░ ░░░░░░░░░░░░░░░░░░░░░░░   ░░ ▒░  ░░░   ░▒░  ░░            " << std::endl;
        std::cout << "                ▒██▒░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒   ▒▒░       ░░░░                  " << std::endl;
        std::cout << "                ▓██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░     ░▒▒▒░                  " << std::endl;
        std::cout << "                ▓██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒░ ░▒▒▒░                  " << std::endl;
        std::cout << "                ▓██░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░ ▒░    ░░░                   " << std::endl;
        std::cout << "                ▓██░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒░   ░██▒                   " << std::endl;
        std::cout << "                ▓██░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░██▒                   " << std::endl;
        std::cout << "                ▓██░▒▒▒▒▓▓██▓▒▒▒▒▒▓████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░██▒                   " << std::endl;
        std::cout << "                ▓██░▒▒████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░██▒                   " << std::endl;
        std::cout << "                ▓█▓░▓███████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░██▒                   " << std::endl;
        std::cout << "                ▒▒▒███████████████▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░██▒                   " << std::endl;
        std::cout << "                ▒███████▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒██▒                   " << std::endl;
        std::cout << "             ░▓███████▒░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████░                   " << std::endl;
        std::cout << "              ░█████▒ ▓███████████████████████████████████░                     " << std::endl;
        std::cout << "                ░█▒░               ░░░░░░░                                      " << std::endl;
        std::cout << "                                  ▒███████░                                     " << std::endl;
        std::cout << "                            ░▓███████████████████                               " << std::endl;
        std::cout << "                             ░░░░░░░░░░░░░░░░░░░░                               " << std::endl;
        std::cout << "                                                                                " << std::endl;
        std::cout << "                                                                                " << std::endl;
        std::cout << " ░▒▒▒▒▒▒░░▒░   ▒▒   ░▒▒░   ▒▒▒▒▒▒▒░   ▒▒▒░    ░▓██████▓▓██████▒▒██████▓▒▓░  ░▓▓░" << std::endl;
        std::cout << " ▒▒░     ▒▒░░░░▒▒  ░▒░░▒░  ▒▒   ░▒░  ▒▒░▒▒░      ░█▒░ ░▓▓▒▓▓▓▒░██░    ░▒█▒▓▓▓█▓░" << std::endl;
        std::cout << " ▒▒░░░░░ ▒▒░  ░▒▒ ░▒░▒▒▒▒░ ▒▒░░░░▒░░▒▒░▒▒▒▒░     ░█▒░ ░▓▓░░░░░░██░░░░░░▒█░  ░▓▓░" << std::endl;
        std::cout << " ░░░░░░░░░░    ░░░░░    ░░░░░░░░░░ ░░░    ░░     ░▒░  ░░▒▒▒▒▒▒░░▒▒▒▒▒▒░░▒░  ░▒▒░" << std::endl;        
     }

    /**
     * Prints welcome message
     */
    void printWelcomeMessage() {
        Utils::setConsoleTextColor(m_uiColor);
        printLogoPart1();
        Utils::setConsoleTextColor("green");
        printLogoPart2();
        Utils::setConsoleTextColor(m_uiColor);
        std::cout << Utils::centerString("", m_displayWidth, "═", "╔", "╗") << std::endl;
        std::cout << Utils::centerString("Welcome to the Corner Grocer Inventory Analyzer", m_displayWidth, " ", "║", "║") << std::endl;
        std::cout << Utils::centerString("Benjamin Orona, Chada Tech", m_displayWidth, " ", "║", "║") << std::endl;
        std::cout << Utils::centerString("", m_displayWidth, "═", "╚", "╝") << std::endl << std::endl;
    }

    /**
     * Tries to build the database.
     *
     * @return true if the database was built successfully, false otherwise
     */
    bool tryBuildDatabase() {
        try {
            Utils::setConsoleTextColor(m_uiColor);
            std::cout << "Preparing database..." << std::endl << std::endl;
            m_database.buildDatabaseFromFile(m_inputFileName);
            std::cout << "Input file read successfully." << std::endl << std::endl;
            m_database.writeDatabaseBackup(m_outputFileName);
            std::cout << "Database backup written successfully." << std::endl << std::endl;
        } catch (const Database::DatabaseError& e) {
            std::cerr << "Fatal Error: " << e.what() << std::endl;
            std::cerr << "The program cannot continue without access to the database." << std::endl << std::endl;
            Utils::waitForEnter();
            return false;
        }
        return true;
    }

    /**
     * Gets heatmap color.
     *
     * @param t_count the count of the item
     * @return the heatmap color
     */
    std::string getHeatmapColor(int t_count) {
        // Calculate the index of the color to use by scaling the count to the range of the color array
        // then dividing by the max item count so the colors are evenly distributed
        int maxItemCount = m_database.getMaxItemCount();
        int colorCount = m_heatMapColors.size();
        int colorIndex = std::round((t_count / static_cast<double>(maxItemCount)) * colorCount) - 1;
        // clamp the color index to the range of the color array
        colorIndex = (colorIndex < 0) ? 0 : (colorIndex > colorCount ? colorCount : colorIndex);
        return m_heatMapColors[colorIndex];
    }

    /**
     * Prints the color key.
     */
    void printColorKey() {
        Utils::setConsoleTextColor(m_uiColor);
        std::string histogramChar = "█";  // Full block Unicode character
        int maxItemCount = m_database.getMaxItemCount();

        // Print the color key
        std::cout << "Color Key: 1 ";
        for (const auto& color : m_heatMapColors) {
            Utils::setConsoleTextColor(color);
            std::cout << histogramChar;
        }
        Utils::setConsoleTextColor(m_uiColor);
        std::cout << " " << maxItemCount << std::endl;
    }

    /**
     * Searches for an item by name.
     */
    void searchForItemByName() {
        Utils::setConsoleTextColor(m_uiColor);
        std::string item;

        // Get the item name from the user
        std::cout << std::endl << "Enter the name of the item to search for: ";
        std::getline(std::cin, item);
        item = Utils::trim(item);
        if (item.empty()) {
            std::cout << std::endl << "Invalid item name" << std::endl << std::endl;
            Utils::waitForEnter();
            return;
        }

        // Try to get the count of the item
        int count;
        if (!m_database.tryGetItemCount(item, count)) {
            std::cout << std::endl << "Item not found" << std::endl << std::endl;
            Utils::waitForEnter();
            return;
        }

        // Print the item and count
        Utils::setConsoleTextColor(getHeatmapColor(count));
        std::cout << std::endl << Utils::centerStrings(item, std::to_string(count), m_displayWidth) << std::endl << std::endl;
        Utils::setConsoleTextColor(m_uiColor);
        Utils::waitForEnter();
    }

    /**
     * Displays the count of all items numerically.
     */
    void displayCountOfAllItemsNumerical() {
        std::map<std::string, int> itemCounts = m_database.getItemCounts();

        // Print the item and count
        for (const auto& item : itemCounts) {
            Utils::setConsoleTextColor(getHeatmapColor(item.second));
            std::cout << Utils::centerStrings(item.first, std::to_string(item.second), m_displayWidth) << std::endl;
            Utils::setConsoleTextColor(m_uiColor);
        }
        std::cout << std::endl;

        // Print the color key
        printColorKey();
        Utils::setConsoleTextColor(m_uiColor);
        std::cout << std::endl;
        Utils::waitForEnter();
    }

    /**
     * Displays the count of all items in a histogram.
     */
    void displayCountOfAllItemsHistogram() {
        std::string histogramChar = "█";  // Full block Unicode character
        std::map<std::string, int> itemCounts = m_database.getItemCounts();

        // Print the item and count
        for (const auto& item : itemCounts) {
            Utils::setConsoleTextColor(getHeatmapColor(item.second));
            std::cout << Utils::centerStrings(item.first, Utils::repeatString(histogramChar, item.second), m_displayWidth) << std::endl;
            Utils::setConsoleTextColor(m_uiColor);
        }
        std::cout << std::endl;

        // Print the color key
        printColorKey();
        Utils::setConsoleTextColor(m_uiColor);
        std::cout << std::endl;
        Utils::waitForEnter();
    }

    /**
     * Main menu loop.
     */
    void mainMenu() {
        while (true) {
            Utils::setConsoleTextColor(m_uiColor);
            Utils::printMenu("Main Menu", m_mainMenuOptions, m_displayWidth);
            std::cout << std::endl;

            // Get the menu choice
            unsigned int choice = Utils::getMenuChoice(m_mainMenuOptions.size());

            // Exit the loop if the user chooses to exit
            if (choice == m_mainMenuOptions.size()) {
                break;
            }

            // Handle the menu choice
            switch (choice) {
                case 1:
                    searchForItemByName();
                    break;
                case 2:
                    displayCountOfAllItemsNumerical();
                    break;
                case 3:
                    displayCountOfAllItemsHistogram();
                    break;
                default:
                    std::cout << "Invalid choice" << std::endl;
            }
            std::cout << std::endl;
        }
    }

public:
    /**
     * Starts the inventory analyzer.
     */
    void Start() {
        // Intro
        Utils::clearScreen();
        printWelcomeMessage();
        Utils::waitForEnter();
        Utils::clearScreen();
        
        // Build the database
        if (!tryBuildDatabase()) {
            return;
        }
        Utils::setConsoleTextColor(m_uiColor);
        std::cout << std::endl << "Database prepared successfully." << std::endl << std::endl;
        Utils::waitForEnter();
        Utils::clearScreen();

        // Main menu loop
        mainMenu();

        // Outro
        Utils::setConsoleTextColor(m_uiColor);
        printChadaTechLogo();
        std::cout << std::endl << Utils::centerString("Thank you for using the Inventory Analyzer!", m_displayWidth) << std::endl;
        std::cout << Utils::centerString("Developed by Chada Tech", m_displayWidth) << std::endl << std::endl;
        Utils::setConsoleTextColor(m_uiColor);
        Utils::waitForEnter();
        Utils::setConsoleTextColor("white");
    }
};

// --- Main Function ---

int main() {
    // Set Windows console to UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    InventoryAnalyzer inventoryAnalyzer;
    inventoryAnalyzer.Start();
    return 0;
}