//
//  22.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

Day 22   Part 2   #include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

#define TIMES_INT 2000

long evolveSecretNumber(long secretNumber) {
    // Step 1: Multiply by 64, mix the result, and prune
    long step1 = secretNumber * 64;
    secretNumber ^= step1;  // Mix using XOR
    secretNumber = secretNumber % 16777216;  // Prune by modulo 16777216

    // Step 2: Divide by 32, round down, mix the result, and prune
    long step2 = secretNumber / 32;  // Perform integer division (rounding down)
    secretNumber ^= step2;  // Mix using XOR
    secretNumber = secretNumber % 16777216;  // Prune by modulo 16777216

    // Step 3: Multiply by 2048, mix the result, and prune
    long step3 = secretNumber * 2048;
    secretNumber ^= step3;  // Mix using XOR
    secretNumber = secretNumber % 16777216;  // Prune by modulo 16777216

    // Return the final evolved secret number
    return secretNumber;
}

int main() {
    
    std::vector<int> vector;  // Vector to store the numbers
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC22.txt");  // Open the file (replace with your actual file path)
    
    if (!inputFile) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;  // Exit with error code
    }

    int number;
    while (inputFile >> number) {  // Read numbers from the file
        vector.push_back(number);  // Add each number to the vector
    }
//    test
//    vector = {1, 2, 3, 2024};
    std::unordered_map<std::string, long> map;
    
    for (auto number: vector) {
        long secretNumber = number;
        std::vector<int> sequence;
        std::set<std::string> seen;
        int lastPrice = secretNumber % 10;
        for (int i = 0; i < TIMES_INT; i++) {
            secretNumber = evolveSecretNumber(secretNumber);
            int diff = secretNumber % 10-lastPrice;
            sequence.push_back(diff);
            
            if(sequence.size() >= 4) {
                std::vector<int> subArray(sequence.end() - 4, sequence.end());
                std::string key;
                for (int i = 0; i < subArray.size(); ++i) {
                    key += std::to_string(subArray[i]) + ".";
                }
                
                if (!seen.contains(key)) {
                    seen.insert(key);
                    map[key] += secretNumber % 10;
                }
            }
            lastPrice = secretNumber % 10;
        }
    }
    long result = 0;
    for (auto pair: map) {
        std::cout << "key number: " << pair.first << "value is :" << pair.second << std::endl;
        if (result < pair.second) {
            result = pair.second;
        }
    }
    std::cout << "result number: " << result << std::endl;
    return 0;
}
