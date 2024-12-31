//
//  03.cpp
//  2024
//
//  Created by Jingfu Ju on 12/31/24.
//


#include <iostream>
#include <string>
#include <regex>

#include <fstream>
#include <sstream>
#include <string>



#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <utility>  // For std::pair

#include "03.hpp"

void Solution03::generateSolution() {
    
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC3.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::ostringstream oss; // Create an ostringstream to hold the contents of the file
    oss << inputFile.rdbuf();  // Read the whole file into the string stream
    std::string fileContents = oss.str(); // Convert the ostringstream to a string
    inputFile.close();
    
    // Sample input text with mul, do(), and don't() expressions
    std::string text = "do()" + fileContents;
    

    // Combined regular expression to match mul() expressions and do()/don't() expressions
    std::regex combined_regex("mul\\((\\d+),(\\d+)\\)|do\\(.*?\\)|don't\\(.*?\\)");

    // Vector to store extracted numbers from mul()
    std::vector<std::pair<int, int>> numbers;
    std::smatch match;
    std::string::const_iterator searchStart(text.cbegin());
    
    std::cout << "Processing mul(), do(), and don't() expressions:\n";
    bool skip = false;
    while (searchStart != text.cend()) {
        if (std::regex_search(searchStart, text.cend(), match, combined_regex)) {
            
            if (!skip && match[0].str().find("mul") == 0) {
                int num1 = std::stoi(match[1].str()); // First number
                int num2 = std::stoi(match[2].str()); // Second number
                numbers.push_back({num1, num2});
            } else if (match[0].str().find("don't") == 0) {
                skip = true;
            } else if (match[0].str().find("do") == 0) {
                skip = false;
            }
            searchStart = match.suffix().first;
        } else {
            break;
        }
    }

    int result = 0;
    for (const auto& pair : numbers) {
        result += pair.first * pair.second;
    }
    std::cout << "Solution 03: " << result << "\n";
}
