//
//  05.hpp
//  2024
//
//  Created by Jingfu Ju on 12/31/24.
//




- [x] Day 5
Part 1  
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <map>


bool isSubsequence(std::vector<int> arr, std::vector<int> pattern) {
    
    int i = 0;
    int j = 0;
    
    while (i < pattern.size()) {
        if (pattern[i] == arr[j]) {
            j += 1;
        }
        if (j == arr.size()) { return true; }
        i += 1;
    }
    return false;
}

int main() {
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC5.txt");  // Replace with your file path
    std::string line;
    
    // Data structures to store the parsed data
    std::vector<std::pair<int, int>> pairData;
    std::vector<std::vector<int>> listData;
    
    // Check if the file opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }
    
    
    
    std::map<int, std::set<int>> before;
    std::map<int, std::set<int>> after;
    std::unordered_map<int, int> inbound;
    
    
    
    // Read each line of the file
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        
        if (line.find('|') != std::string::npos) {
            // Parse lines with "|"
            int first, second;
            char delimiter;  // to read the '|' character
            
            ss >> first >> delimiter >> second;
            before[second].insert(first);
            after[first].insert(second);
            
            inbound[second] += 1;
            pairData.push_back(std::make_pair(first, second));
        }
        else if (line.find(',') != std::string::npos) {
            // Parse lines with ","
            std::vector<int> row;
            std::string number;
            
            // Split by commas
            while (std::getline(ss, number, ',')) {
                row.push_back(std::stoi(number));
            }
            listData.push_back(row);
        }
    }
    
    inputFile.close();
    
    
    std::vector<int> orderedsequence;
    
    
//    int curr = 0;
//    for (std::pair pair : pairData) {
////        if (pair.second == pair.first) {
////            break;
////        }
//        std::cout << pair.first << "|" << pair.second << std::endl;
//        if (!map.contains(pair.first)) {
//            curr = pair.first;
//            orderedsequence.push_back(curr);
//            break;
//        }
//    }

//    int counter = 0;
//    while (counter < map.size()) {
//        for (const auto& pair  : map) {
//            if (pair.second.contains(curr) && inbound[pair.first] == 1) {
//                orderedsequence.push_back(pair.first);
//                counter += 1;
//                curr = pair.first;
//                continue;
//            } else if (pair.second.contains(curr)) {
//                inbound[pair.first] --;
//            }
//        }
//    }

    // Output the parsed data (optional, for verification)
//    std::cout << "\n\nOrdered Sequence:" << std::endl;
//    for (const auto& p : orderedsequence) {
//        std::cout << p << ",";
//    }
    

    int result = 0;
    
    for (const auto& list : listData) {
        int i = 0;
        for (; i < list.size()-1; i++) {
            if (!before[list[i+1]].contains(list[i])) {
                break;
            }
        }
        if (i == list.size()-1) {
            result += list[list.size()/2];
        }
        
        
//        if (isSubsequence(list, orderedsequence)) {
//            std::cout << "\nmid (comma separated):\n" << list[list.size()/2] << std::endl;
//            result += list[list.size()/2];
//        }
    }
    std::cout << "\nresult is (" << result << "):" << std::endl;
    return 0;
}


Part2:

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <map>



int main() {
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC5.txt");  // Replace with your file path
    std::string line;
    
    // Data structures to store the parsed data
    std::vector<std::pair<int, int>> pairData;
    std::vector<std::vector<int>> listData;
    
    // Check if the file opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }
    
    
    
    std::map<int, std::set<int>> before;
    std::map<int, std::set<int>> after;
    std::unordered_map<int, int> inbound;
    
    
    
    // Read each line of the file
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        
        if (line.find('|') != std::string::npos) {
            // Parse lines with "|"
            int first, second;
            char delimiter;  // to read the '|' character
            
            ss >> first >> delimiter >> second;
            before[second].insert(first);
            after[first].insert(second);
//            pairData.push_back(std::make_pair(first, second));
        }
        else if (line.find(',') != std::string::npos) {
            // Parse lines with ","
            std::vector<int> row;
            std::string number;
            
            // Split by commas
            while (std::getline(ss, number, ',')) {
                row.push_back(std::stoi(number));
            }
            listData.push_back(row);
        }
    }
    
    inputFile.close();
    

    int result = 0;
    for (const auto& list : listData) {
        
        std::vector<int> sortedList;
        
        for (int i = 0; i < list.size()-1; i++) {
            if (!before[list[i+1]].contains(list[i])) {
                
                std::set<int> visited;
                while (visited.size() != list.size()) {
                    for (int j = 0; j < list.size(); j++) {
                        int counter = list.size() - visited.size() - 1;
                        for (int k = 0; k < list.size(); k++) {
                            if (visited.contains(k)) { continue;}
                            if (j == k) { continue; }
                            
                            if (!after[list[k]].contains(list[j])) {
                                counter -= 1;
                            }
                        }
                        if (counter == 0) {
                            sortedList.push_back(list[j]);
                            visited.insert(j);
                        }
                    }
                }
                
                result += sortedList[sortedList.size()/2];
                
                for (const auto&num : sortedList) {
                    std::cout << num << ",";
                }
                std::cout << std::endl;
                break;
            }
        }
    }
    std::cout << "\nresult is (" << result << "):" << std::endl;
    return 0;
}
