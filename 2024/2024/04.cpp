//
//  04.cpp
//  2024
//
//  Created by Jingfu Ju on 12/31/24.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>


#include "04.hpp"


void Solution04::generateSolution() {
    
    std::vector<std::vector<char>> array;
    size_t maxCols = 0;
    
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC4.txt");
    if (!inputFile) {
        std::cerr << "Unable to open file\n";
        return;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<char> row;
        for (char ch : line) {
            row.push_back(ch);
        }
        if (row.size() > maxCols) {
            maxCols = row.size();
        }
        array.push_back(row);
    }
    inputFile.close();
    
    
    
    const char pattern[] = {'X', 'M', 'A', 'S'};
    
    int counter = 0;
    int k = 0;
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < maxCols; j++) {
            
            if (array[i][j] != 'X') { continue; }
            
            k = 0;
            while (k < 4 && j+3 < maxCols) {
                if (array[i][j+k] == pattern[k]) {
                    k += 1;
                } else {
                    break;
                }
            }
            if (k==4) { counter += 1; }
            
            k = 0;
            while (k < 4 && j-3 >= 0) {
                if (array[i][j-k] == pattern[k]) {
                    k += 1;
                } else {
                    break;
                }
            }
            if (k==4) { counter += 1; }
            
            
            k = 0;
            while (k < 4 && j-3 >= 0 && i-3 >= 0) {
                if (array[i-k][j-k] == pattern[k]) {
                    k += 1;
                } else {
                    break;
                }
            }
            if (k==4) { counter += 1; }
            
            k = 0;
            while (k < 4 && j-3 >= 0 && i+3 < array.size()) {
                if (array[i+k][j-k] == pattern[k]) {
                    k += 1;
                } else {
                    break;
                }
            }
            if (k==4) { counter += 1; }
            
            k = 0;
            while (k < 4 && j+3 < maxCols && i-3 >= 0) {
                if (array[i-k][j+k] == pattern[k]) {
                    k += 1;
                } else {
                    break;
                }
            }
            if (k==4) { counter += 1; }
            
            k = 0;
            while (k < 4 && j+3 < maxCols && i+3 < array.size()) {
                if (array[i+k][j+k] == pattern[k]) {
                    k += 1;
                } else {
                    break;
                }
            }
            if (k==4) { counter += 1; }
            
            
            k = 0;
            while (k < 4 && i+3 < array.size()) {
                if (array[i+k][j] == pattern[k]) {
                    k += 1;
                } else {
                    break;
                }
            }
            if (k==4) { counter += 1; }
            
            
            k = 0;
            while (k < 4 && i-3 >=0) {
                if (array[i-k][j] == pattern[k]) {
                    k += 1;
                } else {
                    break;
                }
            }
            if (k==4) { counter += 1; }
        }
    }
    std::cout << "Solution 04 - part1: " << counter << std::endl;
    
    
    std::set<char> pattern2 = {'M', 'S'};
    counter = 0;
    k = 0;
    for (int i = 0; i < array.size(); i++) {
        for (int j = 0; j < maxCols; j++) {
            if (array[i][j] != 'A') { continue; }
            
            if (i-1>=0 && i+1<array.size() && j-1>=0 && j+1<maxCols) {
                std::set<char> set1;
                std::set<char> set2;
                
                set1.insert(array[i-1][j-1]);
                set1.insert(array[i+1][j+1]);
                
                set2.insert(array[i-1][j+1]);
                set2.insert(array[i+1][j-1]);
                
                if (set1 == pattern2 && set2 == pattern2) {
                    counter += 1;
                }
            }
        }
    }
    std::cout << "Solution 04 - part2: " << counter << std::endl;
}



