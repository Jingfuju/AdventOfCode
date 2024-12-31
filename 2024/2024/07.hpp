//
//  07.hpp
//  2024
//
//  Created by Jingfu Ju on 12/31/24.
//


- [x] Day 7

Part 2:
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    // Open the file
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC7.txt");

    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Vector to store the 2D data (each row is a vector of integers)
    std::vector<std::vector<long long>> data;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);

        long key;
        ss >> key;  // Read the key (first integer)

        // Skip the colon (:) after the key using std::getline
        char colon;
        ss >> colon;  // This will ignore the colon ':'

        // Vector to store the values associated with the key
        std::vector<long long> values;
        values.push_back(key);  // Include the key in the same row

        long value;
        // Read the remaining values in the line
        while (ss >> value) {
            values.push_back(value);
        }

        // Store the row of values (key + associated values)
        data.push_back(values);
    }

    inputFile.close();  // Close the file
    for (const auto& row : data) {
        std::cout << std::endl;
        for (long long val : row) {
            std::cout << val << " ";
        }
    }
    // body
    
    long result = 0;
    for (const auto& row : data) {

        std::queue<long long> queue;
        queue.push(row[1]);
        for (int i = 2; i < row.size(); i++) {
            
            long capacity = queue.size();
            for (int k = 0; k < capacity; k++) {
                long long curr = queue.front();
                queue.push(curr * row[i]);
                queue.push(curr + row[i]);
                
                std::string str = std::to_string(curr) + std::to_string(row[i]);
                queue.push(std::stol(str));
                queue.pop();
            }
        }
        while (!queue.empty()) {
            if (queue.front() == row[0]) {
                result += row[0];
                break;
            }
            queue.pop();
        }
        
        std::cout << std::endl;
        for (long long val : row) {
            std::cout << val << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "result is: " << result << std::endl;
    return 0;
}

