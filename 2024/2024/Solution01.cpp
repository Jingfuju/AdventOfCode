//
//  Solution01.cpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Solution01.hpp"

using namespace std;

void Solution01::generateSolution() {
    
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC1.txt"); // Replace with the actual file name
    std::string line, value;
    std::vector<int> array1, array2;
    std::string token;
    
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
    }
    
    int num1, num2;
    while (file >> num1 >> num2) {
        array1.push_back(num1);
        array2.push_back(num2);
    }
    
    file.close();
    
    std::unordered_map<int, int> map;
    for (double val : array2) {
        if (map.contains(val)) {
            map[val] += 1;
        } else {
            map[val] = 1;
        }
    }
    
    int result = 0;
    for (double val : array1) {
        if (map.contains(val)) {
            result += val * map[val];
        }
    }
    std::cout << "Solution 01 - part01: " << result << std::endl;
}
