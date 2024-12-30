//
//  01.cpp
//  2024
//
//  Created by Jingfu Ju on 12/29/24.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <regex>
#include <assert.h>

#include "Solution19.hpp"

using namespace std;

std::string removeLeadingSpaces(const std::string& str) {
    std::regex leading_spaces("^\\s+");\
    return std::regex_replace(str, leading_spaces, "");
}


void Solution19::generateSolution() {
    
    std::vector<std::string> vectorData;  // To store the first part of the data
    std::set<std::string> setData;
    
    // Read from file
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC19.txt");  // Open the file to read
    if (!inputFile) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }
     // To store the second part of the data
    std::string line;
    bool emptyLineFound = false;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            emptyLineFound = true;
            continue;
        }

        if (!emptyLineFound) {
            std::stringstream ss(line);
            std::string word;
            while (std::getline(ss, word, ',')) {
                setData.insert(removeLeadingSpaces(word));
           }
        } else {
            vectorData.push_back(line);
        }
    }
    inputFile.close();

    
    int counter = 0;
    for (int i = 0; i < vectorData.size(); i++) {
        int size = static_cast<int>(vectorData[i].size());
        std::vector<bool> mark(size+1, false);
        mark[0] = true;
        
        std::string sentence = vectorData[i];
        for (int k = 0; k < sentence.size(); k++) {
            for (int index = 0; index <= k; index ++) {
                
                std::string word = sentence.substr(index, k-index+1);
                if (!setData.contains(word)) { continue; }
                if (mark[index]) {
                    mark[k+1] = true;
                    break;
                }
            }
        }
        if (mark[mark.size()-1]) { counter += 1; }
    }
    std::cout << "Solution 1 for 19 is: " << counter << std::endl;
    
    
    // Part 2
    long counter2 = 0;
    for (int i = 0; i < vectorData.size(); i++) {
       int size = static_cast<int>(vectorData[i].size());
       
       std::vector<long> mark(size+1, 0);
       mark[0] = 1;
       
       std::string sentence = vectorData[i];
       for (int k = 0; k < sentence.size(); k++) {
           for (int index = 0; index <= k; index ++) {
               
               std::string word = sentence.substr(index, k-index+1);
               if (setData.contains(word)) {
                   mark[k+1] += mark[index];
               }
           }
       }
        counter2 += mark.back();
    }
    std::cout << "Solution 2 for 19 is: " << counter2 << std::endl;
    return;
}
