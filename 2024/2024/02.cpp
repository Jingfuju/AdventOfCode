//
//  02.cpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "02.hpp"

using namespace std;


bool isValid(std::vector<int> nums) {
    int last = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        int diff = nums[i] - last;
        if (diff >= 1 && diff <= 3) {
            last = nums[i];
        } else {
            return false;
        }
    }
    return true;
}


bool canBeStrictlyIncreasing(std::vector<int> nums) {
  
    std::vector<int> nums1(nums);
    std::vector<int> nums2(nums);
    
    for(int i=0; i<nums.size()-1; i++){
        if(nums[i]>=nums[i+1] || nums[i+1]-nums[i] < 1 || nums[i+1]-nums[i] > 3){
            nums1.erase(nums1.begin() + i);
            nums2.erase(nums2.begin() + i + 1);
            break;
        }
    }
    return isValid(nums1) || isValid(nums2);
}



void Solution02::generateSolution() {
    
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC2.txt"); // Replace with the actual file name
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
    }

    std::string line, value;
    std::string token;
    std::vector<vector<int>> vector;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        ::vector<int> row;
        while (getline(ss, token, ' ')) {
            row.push_back(stoi(token));
        }
        vector.push_back(row);
    }
    file.close();

    
    
    int counter1 = 0;
    int counter2 = 0;
    
    for (auto row: vector) {
        counter1 += 1;
        int last = -1;
        int diff = 0;
        for (auto item : row) {
            if (last == -1) {
                last = item;
            } else {
                int diff1 = item - last;
                int diffAbsolute = abs(diff1);
                if (diffAbsolute >= 1 && diffAbsolute <= 3) {
                    if (diff != 0 && diff1 * diff < 0) {
                        counter1 -= 1;
                        break;
                    }
                    diff = diff1;
                    last = item;
                } else {
                    counter1 -= 1;
                    break;
                }
            }
        }
        
        if (canBeStrictlyIncreasing(row)) {
            counter2++;
        } else {
            reverse(row.begin(), row.end());
            if (canBeStrictlyIncreasing(row)) {
                counter2++;
            }
        }
    }

    std::cout << "Solution 02 - part 01: " << counter1 << std::endl;
    std::cout << "Solution 02 - part 02: " << counter2 << std::endl;
}
