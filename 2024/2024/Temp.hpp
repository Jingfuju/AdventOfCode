//
//  Temp.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//


- [x] Day 3

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

int main() {
    
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC3.txt");

    // Check if the file was opened successfully
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;  // Exit with error code
    }

    // Create an ostringstream to hold the contents of the file
    std::ostringstream oss;
    oss << inputFile.rdbuf();  // Read the whole file into the string stream

    // Convert the ostringstream to a string
    std::string fileContents = oss.str();
    inputFile.close();
    
    // Sample input text with mul, do(), and don't() expressions
    std::string text = "do()" + fileContents;
    

    // Combined regular expression to match mul() expressions and do()/don't() expressions
    std::regex combined_regex("mul\\((\\d+),(\\d+)\\)|do\\(.*?\\)|don't\\(.*?\\)");

    // Vector to store extracted numbers from mul()
    std::vector<std::pair<int, int>> numbers;

    // Iterator for matching mul(), do(), and don't() expressions
    std::smatch match;
    std::string::const_iterator searchStart(text.cbegin());

    // Process the entire text in one pass, checking for mul(), do(), and don't() expressions
    std::cout << "Processing mul(), do(), and don't() expressions:\n";
    bool skip = false;
    while (searchStart != text.cend()) {
        if (std::regex_search(searchStart, text.cend(), match, combined_regex)) {
            // Check if it's a mul() expression
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
    std::cout << "result is (" << result << ")\n";
    return 0;
}


- [x] Day4

Part1:
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int main() {
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC4.txt"); // Open file
    if (!inputFile) {
        std::cerr << "Unable to open file\n";
        return 1;
    }

    std::vector<std::vector<char>> array;  // To store the data (2D vector)
    std::string line;
    size_t maxCols = 0;  // Track the max number of columns in any line

    while (std::getline(inputFile, line)) {
        std::vector<char> row;  // A row to store characters of the current line

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
    std::cout << "result is (" << counter << ")" << std::endl;
    return 0;
}


Part2:
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int main() {
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC4.txt"); // Open file
    if (!inputFile) {
        std::cerr << "Unable to open file\n";
        return 1;
    }

    std::vector<std::vector<char>> array;  // To store the data (2D vector)
    std::string line;
    size_t maxCols = 0;  // Track the max number of columns in any line

    while (std::getline(inputFile, line)) {
        std::vector<char> row;  // A row to store characters of the current line

        for (char ch : line) {
            row.push_back(ch);
        }
        if (row.size() > maxCols) {
            maxCols = row.size();
        }
        array.push_back(row);
    }

    inputFile.close();
    
    
    std::set<char> pattern = {'M', 'S'};
    
    int counter = 0;
    int k = 0;
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
                
                if (set1 == pattern && set2 == pattern) {
                    counter += 1;
                }
            }
        }
    }
    std::cout << "result is (" << counter << ")" << std::endl;
    return 0;
}



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




- [x] Day 6  Part 1:
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int main() {
    // Create a vector of vectors to store the grid
    std::vector<std::vector<char>> grid;

    // Open the file
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC6.txt");
    
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        // Convert the line (string) into a vector of characters
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    // Close the file
    file.close();

    // Now `grid` contains the 2D array of characters
    // Print the grid to verify
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, // Up
        {0, 1},  // Right
        {1, 0},  // Down
        {0, -1} // Left
    };
    
    std::pair<int, int> start = {0, 0};
    
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '^') {
                start = {i, j};
            }
        }
    }
    
    int result = 0;
    
    int i = start.first;
    int j = start.second;
    int mark = 0;
    
    int m = grid.size();
    int n = grid[0].size();
    
    std::set<int> visited;
    visited.contains(i*n+j);
    auto isValid = [&m, &n](int i, int j) {
        return i >= 0 && j >= 0 && i < m && j < n;
    };
    
    int nextX = i + directions[mark].first;
    int nextY = j + directions[mark].second;
    while (true) {
    
        if (!isValid(nextX, nextY)) {
            std::cout << std::endl;
            for (const auto& row : grid) {
                for (char cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
            break;
        }
        
        // rotate
        if (isValid(nextX, nextY) && grid[nextX][nextY] == '#') {
            nextX -= directions[mark].first;
            nextY -= directions[mark].second;
            mark = (mark + 1) % 4;
            nextX += directions[mark].first;
            nextY += directions[mark].second;
        }
    
        while(isValid(nextX, nextY) && grid[nextX][nextY] != '#') {
            
            if (grid[nextX][nextY] != 'X') {
                result += 1;
            }
//            if (!visited.contains(nextX*n+nextY)) {
//                result += 1;
//            }
            grid[nextX][nextY] = 'X';
//            visited.insert(nextX*n+nextY);
            nextX += directions[mark].first;
            nextY += directions[mark].second;
        }
    }
    
    std::cout << "result is : " << result << std::endl;
    return 0;
}


Part 2:
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int main() {
    // Create a vector of vectors to store the grid
    std::vector<std::vector<char>> grid;

    // Open the file
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC6.txt");
    
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        // Convert the line (string) into a vector of characters
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    // Close the file
    file.close();

    // Now `grid` contains the 2D array of characters
    // Print the grid to verify
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, // Up
        {0, 1},  // Right
        {1, 0},  // Down
        {0, -1} // Left
    };
    
    std::pair<int, int> start = {0, 0};
    
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '^') {
                start = {i, j};
            }
        }
    }
    
    int result = 0;
    int m = grid.size();
    int n = grid[0].size();
    
    // inbound check
    auto isValid = [&m, &n](int i, int j) {
        return i >= 0 && j >= 0 && i < m && j < n;
    };

    
    for (int row = 0; row < n; row++) {
        
        for (int col = 0; col < m; col++) {
            if (grid[row][col] != '#') {
                grid[row][col] = '#';
                
                int mark = 0;
                std::unordered_map<int, std::set<int>> unordered_map;
                unordered_map[start.first*n+start.second].insert(mark);
                
                int nextX = start.first + directions[mark].first;
                int nextY = start.second + directions[mark].second;
                
                while (true) {
                    
                    if (!isValid(nextX, nextY)) {
                        
//                         Debug
//                        std::cout << std::endl;
//                        for (const auto& row : grid) {
//                            for (char cell : row) {
//                                std::cout << cell << " ";
//                            }
//                            std::cout << std::endl;
//                        }
//                         Debug end
                        break;
                    }
                    
                    
                    
                    // rotate
                    if (isValid(nextX, nextY) && grid[nextX][nextY] == '#') {
                        nextX -= directions[mark].first;
                        nextY -= directions[mark].second;
                        
                        int index = nextX*n+nextY;
                        unordered_map[index].insert(mark);
                        mark = (mark + 1) % 4;
                        unordered_map[index].insert(mark);
                        
                        nextX += directions[mark].first;
                        nextY += directions[mark].second;
                    }
                
                    while(isValid(nextX, nextY) && grid[nextX][nextY] != '#') {
                        int index = nextX*n+nextY;
                        if (unordered_map[index].contains(mark)) {
                            result += 1;
                            grid[row][col] = '.';
                            goto jump;
                        } else {
                            unordered_map[index].insert(mark);
                        }
                        nextX += directions[mark].first;
                        nextY += directions[mark].second;
                    }
                }
                
                // trace back
                jump:grid[row][col] = '.';
            }
        }
    }
    std::cout << "result is : " << result << std::endl;
    return 0;
}



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


- [x] Day 8
Part1:  #include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>


int main() {
    // File path (replace with your actual file path)
    std::string filePath = "/Users/jingfuju/Desktop/Advent of Code/AoC8.txt";
    
    // Open the file for reading
    std::ifstream file(filePath);
    
    // Check if the file was successfully opened
    if (!file) {
        std::cerr << "Error opening the file: " << filePath << std::endl;
        return 1;
    }
    
    // Grid to store the map (2D vector)
    std::vector<std::vector<char>> grid;
    std::string line;
    while (std::getline(file, line)) {
        // Create a row (vector of characters) from the line and add it to the grid
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    file.close();
    
    
    
    // body
    
    int result = 0;
    std::unordered_map<char, std::vector<std::vector<int>>> map;
//     Example of processing the grid: Find all the 'A' positions;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); j++) {
            int c = grid[i][j];
            if (c !='.') {
                map[c].push_back({i, j});
            }
        }
    }
    
    int m = grid.size();
    int n = grid[0].size();
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    
    std::set<std::vector<int>> visited;
    for (const auto& pair: map) {
        
        std::vector<std::vector<int>> arr2D = pair.second;

        for (int i = 0; i < arr2D.size()-1; i++) {
            for (int j = i+1; j < arr2D.size(); j++) {
                
                int xDistance = arr2D[j][0] - arr2D[i][0];
                int yDistance = arr2D[j][1] - arr2D[i][1];
                
                
                int leftX = arr2D[i][0] - xDistance;
                int leftY = arr2D[i][1] - yDistance;
            
                
                int rightX = arr2D[j][0] + xDistance;
                int rightY = arr2D[j][1] + yDistance;
                
            
                if (!visited.contains({leftX, leftY}) && isValid(leftX, leftY)) {
                    result += 1;
                    visited.insert({leftX, leftY});
                }
                
              
                if (!visited.contains({rightX, rightY}) && isValid(rightX, rightY)) {
                    result += 1;
                    visited.insert({rightX, rightY});
                }
            }
        }
    }

    std::cout << std::endl;
    std::cout << "result is : " << result << std::endl;
    return 0;
}


Part 2:

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int result = 0;
std::set<std::vector<int>> totalVisited;

std::vector<std::vector<int>> buildBetween(std::vector<std::vector<int>>  vector1, std::vector<std::vector<int>> vector2, int m, int n) {
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    
    std::set<std::vector<int>> visited(vector1.begin(), vector1.end());
    std::vector<std::vector<int>> newVector = vector1;
    
    for (int i = 0; i < vector1.size(); i++) {
        for (int j = 0; j < vector2.size(); j++) {
            if (vector1[i] == vector2[j]) { continue; }
            int xDistance = vector2[j][0] - vector1[i][0];
            int yDistance = vector2[j][1] - vector1[i][1];
            
            
            int x = vector1[i][0] - xDistance;
            int y = vector1[i][1] - yDistance;
            
            while (isValid(x, y)) {
                if (!visited.contains({x, y})) {
                    visited.insert({x, y});
                    newVector.push_back({x, y});
                }
                x = x - xDistance;
                y = y - yDistance;
            }
            
            x = vector2[j][0] + xDistance;
            y = vector2[j][1] + yDistance;
            
            while (isValid(x, y)) {
                if (!visited.contains({x, y})) {
                    visited.insert({x, y});
                    newVector.push_back({x, y});
                }
                x = x + xDistance;
                y = y + yDistance;
            }
        }
    }
    return newVector;
}


int main() {
    // File path (replace with your actual file path)
    std::string filePath = "/Users/jingfuju/Desktop/Advent of Code/AoC8.txt";
    
    // Open the file for reading
    std::ifstream file(filePath);
    
    // Check if the file was successfully opened
    if (!file) {
        std::cerr << "Error opening the file: " << filePath << std::endl;
        return 1;
    }
    
    // Grid to store the map (2D vector)
    std::vector<std::vector<char>> grid;
    std::string line;
    while (std::getline(file, line)) {
        // Create a row (vector of characters) from the line and add it to the grid
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    file.close();
    
    
    
    // body
    std::unordered_map<char, std::vector<std::vector<int>>> map;
//     Example of processing the grid: Find all the 'A' positions;
    for (int i = 0; i < grid.size(); ++i) {
        std::cout << std::endl;
        for (int j = 0; j < grid[0].size(); j++) {
            
            std::cout << grid[i][j] << " ";
            int c = grid[i][j];
            if (c !='.') {
                map[c].push_back({i, j});
            }
        }
    }
    
    
    
    for (const auto& pair: map) {
        
        std::vector<std::vector<int>> arr2D = pair.second;
        std::vector<std::vector<int>> newVector = buildBetween(arr2D, arr2D, grid.size(), grid[0].size());
//        std::vector<std::vector<int>> vector = buildBetween2(arr2D, newVector, grid.size(), grid[0].size());
        
        
        totalVisited.insert(newVector.begin(), newVector.end());
        
        std::set<std::vector<int>> current;
        current.insert(newVector.begin(), newVector.end());
        for (std::vector<int> node: current) {
            std::cout << " " << "(" << node[0] << "," << node[1] << ")"<< std::endl;
            if (grid[node[0]][node[1]] == '.') {
                grid[node[0]][node[1]] = '#';
            }
        }
    }
    
    for (int i = 0; i < grid.size(); ++i) {
        std::cout << std::endl;
        for (int j = 0; j < grid[0].size(); j++) {
            std::cout << grid[i][j] << " ";
        }
    }
    
    result = totalVisited.size();
    std::cout << std::endl;
    std::cout << "result is : " << result << std::endl;
    return 0;
}



- [x] Day 9  Part 1:
#include <iostream>
#include <vector>
#include <string>

int main() {
    // Input number as a string
    std::string number = "6122724455248178535743697228197466561156635199885394732559503849964932256540634832126993189130168437769430885232424013662237288858268344319024945093836182272717435856407569817141251893306258734013352247626698373161653957239014599140467975778966229330353292737643343268382519186684311279263570414619955758562771467095706456306531455830829158305891186429456420687418585540528187739923185747506596606489598717293660943582284650576946378666432961369910541855728547152320597671854010695070919280176117703132541365207868242084122748246660345963132681584922398487482643363792358659373692893812142298697055289074305652165432725560577655774327537645625172799223545061811031806549846725343341921427964845665038857166766671923188161346491349517219787622986199191862314141521573865853402612537157961068307221666994165087243329622491366722113057431659175988294554243364585816147734164335631485681695682619468948728341591518181672539291848051884978555179389129391544635533208668845311609932287843189935308359283778815725706853311490747215342484577880157993747579302698533440981823538532769829308394151574864477885358233225617987455156743827379090705079844031438528578661782022516175166430608766286937617388185887902128567325985189914790802157931496133011652846672428365493491470656829222380808487239513399596273822552975781140467582323166195319631254833929588740998839655872351881445725694188262044167946204146622662439613662316821690381662465014484936292293342391566134202990716847313073136156998521858232241011141066859497366934509933644369958129829273533274119270531071232052673848161384481710577047354521245995118745971026851021142375792920925688207070488041537110857710244754519212698646773296934825958541554146786565438885143875857188541045601384648897217184696537139587984649709148587223668772288433873246672497612167222391498271203060474938697650613086542760441135637154812832774646231083138749705034771198518122478235629017462969916975618589753560276353963284917481934526792362858163747131455817115983618360297576929972499985957457691339186061107088486195232259401066249957425399948741402526687791431139293583675048444031986434599550999133651850774780597321766697384241717143103253543343714671145128638740566921474932809727233052611152338941901139573552802022666779994798617774277553364384397588787736778116905947155336372674164196812486648893135375419122413489601245696917973457361758141020204111625253953192587714252873578161821684445934992214387994398552534572141579777241106463838829835435182381924574166689507778811885994563563815756690189482203172324078577569101670564490158116149412866791825934208542717477258023417418558728624044117012132269259372703139475542834079301615557127154052701762549865139887624663796917768848955972584719211573942043183961776056135878343094461758298667483451108263274488307580638246194686925918409757269236817484773967629559484354369834431236544610249593527669118810456575213434129038516394749933607551309739914170653941525658681633308374583440943695474284614378179897193463686550819992453556847817399178477519306994673159445770133763359817713670331871702921327876684318914889999498375774171874709864795924223227667142307517511151662371647347897081619625311613324428426075684581964551244999188211466173227638201113417044767631715229803687934160829132871916451863692140252612609613738077912249439418552130298232251295434227548593562676143093463960797746984053627534853940874656688161572360655852949389464025866987379498673472951356543817592146237150818182272130368781553575226519362559383131866072901920691526627628579071417421741543658825584323335071116017737977832415571635951616423143489452545182333846233264487841325674862042618256152637344397379345155735653543836443355776582269232259324642975595821316259445483744739032361681897184904560321212854876185453346283986518552918323348248020428150326839193574921568165713402737949896566586543468965891526722443172575788766291823925133517237637291724774646789213497466101486987025371175128399355330987357205494582310865046781210618493115146385392981718671589868592422320926922248711364019239929204881722091338754746471981356885265837242611177312514769252937931752235426067918264935581189478197723959086443964559885633010162823899347765154594663538984348521341069797555219474412470428973607085833430495643228358405579953368197347935182652236577884145815827079477128725970606785436060127543785637888294182232639158765431251172117146276896589069129189508370912899401870105829554130176486138468288771954573674933568186391615197660691386169598548777683139837770972530583770466581539317448761789778696210804568934518832523478523714463103436715755569122565860893037835595264265517662872125333381693592567410926486655667208023697214454269538170558394902440157533833295614592921434248197471677923918601752417856699973947067139194939150709071991712556297968594678711319074386835326051104994807452217769438594717316627565602394815949764994386920517324281792288930284714799890722867724027262630751120492484608994695652339627874471979630707150409439134240215186386739966886112346478819548949388753656716411834413747904872196449714437786245867860211867264718578213489920429661339483221390905729492561631261393053684238699081185669246411844415366299754266906759527384442382453756641322542231397070543256261783113951659989782689174971651217929955908118606082682267225974361682693818825146552960772960887940184050709810278799684143752621588549406687659996925986872537318145175744979233116625577299231982548518283233347334786517903074364434739711847291528848639257287590593288204497549363687538137958101871708796138450414573484212824196177563836820745776124379181184903118328929348562473162715794198138432365477563893813639913597481449044666857626494371486185749995246146930402272501619781734408753595211779462933294306746868138174633155133525226766213797393658451655541251620585937606962253639911186477333512399202915875130202117309117443153666520955362355929798410541870379168434939437668882120175435102014478262602633611274639711442049981815656855808749594788239410659290738620523944716879945226794846398726176246619258491958512036915715487434257228983441603345155079368035429424477156471186377367794932654243106765986745623478787044955736415423832676307852996761813988201184693741527684823087259638652365339067945196259855741387826939404037292211485423222778533793357731888064253575449066481945279468768094186484751064636979644362243731296536812223361761748155908629701239954239935322137693817515788472952225132613321610138498515261498910205895127034597415871975474419554831664532665846832518356154335446818327277143328971743034277996774019468343184657133038185531486456483750828374486494951494598746616097628334262156872546387623243832634627707075402130349455322440696431604486442516321179605132801843941840698810941413414640735215179536297978968561229723602980944784485029267360655544752396636693421521883425646787254082151780372224602872869834339819295689151988408768822660494373436821797096743773511739746360444525283151811365895479149265175730965828166277789615374778531833202340654314527164426921803265356649581218778622794849775547725057669234192459996261358632999023372235852571922234652570601184519046529641496682963020523246868624673794469627538272167943748469793190312753171188417820993720469048717258287811131384635416394999427772562276357844308039425291544764133545353348189812675979903386261734857262754619508561805760121289863212971561799625932662707420301422976258309015691070353726519991677780196757431891418440608999541932445478818553764930435547321739199497334532105770385730464552776022861469149550551175355450815087134749439083811616251658877489407232569373346884326992653810971833394161282680996776658476921935887150998941791487587313218958905994759923138742387014474864733776369236315179585751322068929589487641756029203965146290566856713695303426742542162798849390369243506234553639668475492658107810985763778337663549894165393918556516844326687946314040746062261761848768682971194020724780268877452620245144587959972564351151306795768698559235656551491886133265746242141191747036598548869838488428906113489152703498142238225723968065985156272197496122428820475589471269894789521181504410413014948337813027974929402247215635804012449770718311203830523139905258933163821750675019329651308971979864391584957467727642701429886329685688212292177942734319922510466262752035601968268365241162957188909654444925272812339164294742583142105489758213965123831421126755552622414047915159527934584730214426935412591283301749851165759212429354128359731549547462507637174830753679965280316789616471333945123737614293778039262430513399757533982176527859878387778348251896485186752370451132315180844982204038496512757477545488954250403171336120435463956642469226317123472830939052406280987312121635103171166760432046777873168856214111717941818480343324857237468974654354245088787754204312253115179914547518282292893960871518817444841447266646595688732313189211625310365463123422543216243285882682324196403499999199262065818385736018314314285144977751547743641348627051598081498453981321742215493367719285367880739881232858424483579281808273469861719596446436314590189292769983411477766191893913977169631957119875579349136281305614481492627652228773582533749827479470392290418282606328213423505081606327326950919142474377406876983181726838449637678370182097567691844978839461869335547061918662244654358814933363523370138558543578475271269926118895717140681845717178521771681353149993455459551220206971133049635893135497481920396479213777241697894795468323709339819431822088195627988822434862598280371891909798387280649159403773906389792360241666391790608158817693188434403840366597399819721040931962105644618015442814739615834439304681273963455194291457602314987027721112833286704410981623921463347334359012567022888434397021502448178062295264674176797858733094823789744825145992654524771821326745213373528074353832374223493027732084537598856537521054829641638518841492809758153750344737394190426384243489985176144225406151937230249872519096772449708471698183468575708578753072843241485511427470266121138374992266995910956445831447732683936539369494258435282245347294707039723385517353896684527437568216585099646688539055973897293496675726668657519479923252481931816449569256805174767041728833158117707258408045368733194753349484723337571310794397422794167942481451289241978318905494369649116656596655703110858811885550184038615959538465638543898255827226177347261290485071281187736080733926634264976858261234113475987643785814341382203263833330758853782554737864873556311799923740368487391745295952421860621090423224627885566622444356786847737920566680399922816588917232427653247386524642641782485450912565777372293783711632473498741952798923202198408326897891793616867687845624304325278779823092538363747325199875892841945013567810759762712419105662944027376875112811669874377312702866952136225418745250663651411616383996382457289621215732382016943963454344922617384421302614983915944171991360652528891048504957685323779576426640467997373319665623192881962791161923787044874660295473358015754895885715746566239563387229939725693212268198801213348687604089817839958088346943629812146243234514182284486598735579393612914564764044296830917910691685265448938859505726269344672165196850193581501388329092647367395840577355812854389591762397663281449044175835104194843974441578567743506112613330153912437973821563868648584839477370983243425499426497161333505090837938982772698124454812308999778070243119132639109818963639688626362247251039326040566094829789315214546982918385978673221971805271973015252455481272854390371793742094111224761412746581439167554273112831747619739641182885124198811724648520475071532275968045387822472069992078392059128062848712349276433953756295867867619476387654334421332393715072741139337164571989402851529630266964138266751933288324186184471444354056511218177166483213214742292678179381386160968157292433282281494133245236691333711276932075752171924553711027259559582660515662533335523827209567941945472094143469293046505522278543675086575023593676125640382775562375725924665892375250935775637420936284629311849186501515953716463775126334969750216567319789827161977887972749557395687446826129301565365427112173968154154543774988752158775759659379944626895829873485132948707389875728353535676013401514828156102120592148514679428790728314731511126243496389152248305724633578408997857023472335191123103570221568626370441946697371683452451743222924348065613020922972771192665366844726157328556073633318458565516578473515637624249647961536666759954384698172421246409843253313652076137049827740616419403888795524375384728752326537377837733543671558988484708785607060446765731244769482697617472720372777824627957578532826193724598321484679718592712611394773114139428073204478191217904121342962346713949334933426671799923150593151313917409592533360316734363629527173417828779328505420775599638165154817636357454226387565114420902786673496632660933260808266936863143718264027176796327289249967108293652446865423548583972298258127371154988990782376683786177412964147638134164323729410338461488559247446213111603959366252917131336367872918821961979229547073269124978126655519341958408799945828159815512369654436738420641179617163121972947830996271334653533154234685152049574158152368965566914184746490165123874160678421859667734067639536784572545575336011705771846858188762428915473162449580737327124342434949395731852914313480638051812258717259439394693944709757527111627391395179217017161222689212388799234830972071955491579444832877741718379698366551689126821531266523741998439561496831609858816660281711841676433379867331758278673287277256461068897543709893248591121850129050746547231349928966173129972220635797391386806426659669345864252998699869148114902714693845564025781491807150789098835731448353844656594779425736969830365842455969147119584567161560631928731140482564277523168532319384327620121829763334205770631126609053705492527698772230601767279419275232203212752282259532647163255289706750939881791745386985536327298095234748802641874986656996175533556920431227676331873874689720224579763612854378288526393795851641223348557770135352687245962973467015334245968939407550141671714173453879302736897427347472316284466120145585938121938338835783767041623463337814251893806228525481135411309834507122158469983972837140822881577312882757939451888664464193932016605923697933358637374452756045324471325658929482976111116716112175577093398891166327718610366955608058104650744216587260709286292988846675842839849094733954746391971239427528295962875333513643825852239988376524811177976195809439594785893783554484641753766168118984736274127023863579909310483460724180119557973723776642731287607584193599698081114391399111425494337710252041926339214885723965436912809415581563796380233658541484383337548063241261224196746255257047433489824722328376103378298944693296686853442062415451411235115666777278982913602712321254645066223962945588331251528531885870375272858413989845128432711544595896319786963426801021562838358185704921147815909245694868364334248668105470475989707262359994897954235475511646644937731555625793914627953026756051702241567014578177285436138948977086227591811948817829447195424522957348835074282212745352819270221810891459575974997552191666743747151969487926589436663395274230646583137978618976346560867842383214562543384757162547177149117783605780675634229765974179757067493799291591264758539698591145196010924878825563531422834885875688149365359296137529896560439136631916641621581835482689197551399674191551472597799356619532316899499116476486919195811964816036158526644967961918665387819462939867564245619889267778353824974639934828351010543325891670502135999782354966365676128623206398859742158336536842758172579029801548298381667658878210139268865358679997145272624767372260163379144617445254494125774799665172332933113646546521207082177374795464775595472560267961624897497113189341386643499615258495174021943567407875374688124562137816447696336530121937932728972955341849284992412932338285553129545769862140804152349031949675946223887798871033384225771577172974506523113646144736605389559635193914744816595793417318457353526591122970448928818549234683136941737538348764638468445864903647126451284472794831467929387460995047988317687895854393884443175395756026355258926326148278443133142073387114904822449029657094589218854468172184731216503167313683755386673539355120399956463496133557801136633884286231844511961134873883597364304486632575284270787651293250254343463578627769508571477775506963159462656472191636157976694311883567222366697273884728642523669722484482108392224812562816202327913294192940151712821868755241508064596134191850556256175962997013825294155663523489935596476125187745109189984587442828308257454545281124898934688044374570881340453926531491478780555075216385978124786587964967769520998991456689754014399540977242514470642393278051462749597311112829689863517473665453169358248726524714211197585339622394852832828567671612627564806997296440345425693721271645365043133069531846696195292940582631284472869844913966197946404149444373778778906954101619567835987514208765476835953480537796792643853382191194287065818034314437645428331136959199334777899147747823452584249029647947802790237521753431764449592356727674423180236150201347834065652793362436384666424523936483107580619184789352612271943155537551624623466094191059959269746429904451724184973787235354576973432573949118874815586459553371782630647437728353135546502315403820491880119846796648292077204658354491102437936694307610862823439838176165689370134433221227306744882030149510553813465094344526581966827310124867483172872044421767454838113655157483967356544894366947686576126016845684976188401842341670173641482013549272447159228997356015733094661443641496762950324715973920671162966166282443569413465116752448881913667436115129649853789876148343781016266564857254573636837977759514539264345762966852607928519841739090713581892828737712241139994773219130902668751113981535133440375281968980785394176564492090793732748586603059898958415163804963862943704775967350338299606899218041575492415966926076424995672226312514723117242293406190807778632051385622747967335254558771613856205838578641638852557051324973593697477156455438149729915225865271277292223442911930386139336329489218837913562569295536514530316865793121917399733459818894452665998791212640558333896823973536552864637579328385789332907365923944965674543772568232946517326778189773242225452276791467335219988813975290876654755836633579432946246055845765572889336525488848214185995218726617388095252355399821156743164281966269909987556387726342787363822631722942532974203833997571689516317932213445162626846877524623414831959953117443178948363739255534779015126554767155167422748076839890103567774598123358207259506999802096541837561851554565881535277568602921358937487836932918375864206338648571913881683424402664916664577924807518308119461226355535546621862216349724318053229922211671355572579157937427776469206577818458381121698840129280363647294815747492597784619887953417889599551298147958939777755619611738468398636921157894582978691647335886605885322452245222919523674495575561792189149539344996441650398367856776276558212628745777529347392061989820569988221364575622713353668180697479985433908840124871689589259116746587176185627220222524906933934048905194505488339866944837228594149181233137467786469260819817526776662952309372741916312792558639931091173459893293856777569033851290191136443762505599567392212795898129932818124290389711979572221285284840403782826529927226266390807354953919393623363054187972341893461720688364624573941169177639278979501647243387576421792183343666841452178017482324668523313531991935641273945170495910723235729169649197635589317877559661131852179110201974402232545777332185517523162343367359288315376140588644427172405960946568222654989642341292345352689370972449569980735195519515967476152231952314247523345175901596856839179486728925401886633034913676673649331957247597454839948732342866793250373170774";

    // Create a vector to store the digits
    std::vector<int> digits;

    // Loop through each character in the string
    for (char ch : number) {
        // Convert character to integer and push to the vector
        digits.push_back(ch - '0');
    }

    // Print the elements of the array (vector)
    std::cout << "Array of digits: ";
    std::vector<int> vec;
    
    int curr = 0;
    for (int i = 0; i < digits.size(); i++) {
        if (i%2 == 0) {
            for (int j = 0; j < digits[i]; ++j) {
                vec.push_back(curr);
            }
            curr += 1;
        } else {
            for (int j = 0; j < digits[i]; ++j) {
                vec.push_back(-1);
            }
        }
    }
    
    
    int right = int(vec.size()) - 1;
    while (vec[right] == -1) {
        right -= 1;
    }
    
    for (int i = 0; i < vec.size(); i++) {
        if (i >= right) { break; }
        if (vec[i] == -1) {
            vec[i] = vec[right];
            vec[right] = -1;
        }
        while (vec[right] == -1) {
            right -= 1;
        }
    }

    long long result = 0;
    for (int i = 0; i < vec.size(); i ++) {
        if (vec[i] == -1) { break; }
        result += vec[i] * i;
    }
    std::cout << " result is : " << result << std::endl;
    return 0;
}



Part 2:

#include <iostream>
#include <vector>
#include <string>

int main() {
    // Input number as a string
    std::string number = "6122724455248178535743697228197466561156635199885394732559503849964932256540634832126993189130168437769430885232424013662237288858268344319024945093836182272717435856407569817141251893306258734013352247626698373161653957239014599140467975778966229330353292737643343268382519186684311279263570414619955758562771467095706456306531455830829158305891186429456420687418585540528187739923185747506596606489598717293660943582284650576946378666432961369910541855728547152320597671854010695070919280176117703132541365207868242084122748246660345963132681584922398487482643363792358659373692893812142298697055289074305652165432725560577655774327537645625172799223545061811031806549846725343341921427964845665038857166766671923188161346491349517219787622986199191862314141521573865853402612537157961068307221666994165087243329622491366722113057431659175988294554243364585816147734164335631485681695682619468948728341591518181672539291848051884978555179389129391544635533208668845311609932287843189935308359283778815725706853311490747215342484577880157993747579302698533440981823538532769829308394151574864477885358233225617987455156743827379090705079844031438528578661782022516175166430608766286937617388185887902128567325985189914790802157931496133011652846672428365493491470656829222380808487239513399596273822552975781140467582323166195319631254833929588740998839655872351881445725694188262044167946204146622662439613662316821690381662465014484936292293342391566134202990716847313073136156998521858232241011141066859497366934509933644369958129829273533274119270531071232052673848161384481710577047354521245995118745971026851021142375792920925688207070488041537110857710244754519212698646773296934825958541554146786565438885143875857188541045601384648897217184696537139587984649709148587223668772288433873246672497612167222391498271203060474938697650613086542760441135637154812832774646231083138749705034771198518122478235629017462969916975618589753560276353963284917481934526792362858163747131455817115983618360297576929972499985957457691339186061107088486195232259401066249957425399948741402526687791431139293583675048444031986434599550999133651850774780597321766697384241717143103253543343714671145128638740566921474932809727233052611152338941901139573552802022666779994798617774277553364384397588787736778116905947155336372674164196812486648893135375419122413489601245696917973457361758141020204111625253953192587714252873578161821684445934992214387994398552534572141579777241106463838829835435182381924574166689507778811885994563563815756690189482203172324078577569101670564490158116149412866791825934208542717477258023417418558728624044117012132269259372703139475542834079301615557127154052701762549865139887624663796917768848955972584719211573942043183961776056135878343094461758298667483451108263274488307580638246194686925918409757269236817484773967629559484354369834431236544610249593527669118810456575213434129038516394749933607551309739914170653941525658681633308374583440943695474284614378179897193463686550819992453556847817399178477519306994673159445770133763359817713670331871702921327876684318914889999498375774171874709864795924223227667142307517511151662371647347897081619625311613324428426075684581964551244999188211466173227638201113417044767631715229803687934160829132871916451863692140252612609613738077912249439418552130298232251295434227548593562676143093463960797746984053627534853940874656688161572360655852949389464025866987379498673472951356543817592146237150818182272130368781553575226519362559383131866072901920691526627628579071417421741543658825584323335071116017737977832415571635951616423143489452545182333846233264487841325674862042618256152637344397379345155735653543836443355776582269232259324642975595821316259445483744739032361681897184904560321212854876185453346283986518552918323348248020428150326839193574921568165713402737949896566586543468965891526722443172575788766291823925133517237637291724774646789213497466101486987025371175128399355330987357205494582310865046781210618493115146385392981718671589868592422320926922248711364019239929204881722091338754746471981356885265837242611177312514769252937931752235426067918264935581189478197723959086443964559885633010162823899347765154594663538984348521341069797555219474412470428973607085833430495643228358405579953368197347935182652236577884145815827079477128725970606785436060127543785637888294182232639158765431251172117146276896589069129189508370912899401870105829554130176486138468288771954573674933568186391615197660691386169598548777683139837770972530583770466581539317448761789778696210804568934518832523478523714463103436715755569122565860893037835595264265517662872125333381693592567410926486655667208023697214454269538170558394902440157533833295614592921434248197471677923918601752417856699973947067139194939150709071991712556297968594678711319074386835326051104994807452217769438594717316627565602394815949764994386920517324281792288930284714799890722867724027262630751120492484608994695652339627874471979630707150409439134240215186386739966886112346478819548949388753656716411834413747904872196449714437786245867860211867264718578213489920429661339483221390905729492561631261393053684238699081185669246411844415366299754266906759527384442382453756641322542231397070543256261783113951659989782689174971651217929955908118606082682267225974361682693818825146552960772960887940184050709810278799684143752621588549406687659996925986872537318145175744979233116625577299231982548518283233347334786517903074364434739711847291528848639257287590593288204497549363687538137958101871708796138450414573484212824196177563836820745776124379181184903118328929348562473162715794198138432365477563893813639913597481449044666857626494371486185749995246146930402272501619781734408753595211779462933294306746868138174633155133525226766213797393658451655541251620585937606962253639911186477333512399202915875130202117309117443153666520955362355929798410541870379168434939437668882120175435102014478262602633611274639711442049981815656855808749594788239410659290738620523944716879945226794846398726176246619258491958512036915715487434257228983441603345155079368035429424477156471186377367794932654243106765986745623478787044955736415423832676307852996761813988201184693741527684823087259638652365339067945196259855741387826939404037292211485423222778533793357731888064253575449066481945279468768094186484751064636979644362243731296536812223361761748155908629701239954239935322137693817515788472952225132613321610138498515261498910205895127034597415871975474419554831664532665846832518356154335446818327277143328971743034277996774019468343184657133038185531486456483750828374486494951494598746616097628334262156872546387623243832634627707075402130349455322440696431604486442516321179605132801843941840698810941413414640735215179536297978968561229723602980944784485029267360655544752396636693421521883425646787254082151780372224602872869834339819295689151988408768822660494373436821797096743773511739746360444525283151811365895479149265175730965828166277789615374778531833202340654314527164426921803265356649581218778622794849775547725057669234192459996261358632999023372235852571922234652570601184519046529641496682963020523246868624673794469627538272167943748469793190312753171188417820993720469048717258287811131384635416394999427772562276357844308039425291544764133545353348189812675979903386261734857262754619508561805760121289863212971561799625932662707420301422976258309015691070353726519991677780196757431891418440608999541932445478818553764930435547321739199497334532105770385730464552776022861469149550551175355450815087134749439083811616251658877489407232569373346884326992653810971833394161282680996776658476921935887150998941791487587313218958905994759923138742387014474864733776369236315179585751322068929589487641756029203965146290566856713695303426742542162798849390369243506234553639668475492658107810985763778337663549894165393918556516844326687946314040746062261761848768682971194020724780268877452620245144587959972564351151306795768698559235656551491886133265746242141191747036598548869838488428906113489152703498142238225723968065985156272197496122428820475589471269894789521181504410413014948337813027974929402247215635804012449770718311203830523139905258933163821750675019329651308971979864391584957467727642701429886329685688212292177942734319922510466262752035601968268365241162957188909654444925272812339164294742583142105489758213965123831421126755552622414047915159527934584730214426935412591283301749851165759212429354128359731549547462507637174830753679965280316789616471333945123737614293778039262430513399757533982176527859878387778348251896485186752370451132315180844982204038496512757477545488954250403171336120435463956642469226317123472830939052406280987312121635103171166760432046777873168856214111717941818480343324857237468974654354245088787754204312253115179914547518282292893960871518817444841447266646595688732313189211625310365463123422543216243285882682324196403499999199262065818385736018314314285144977751547743641348627051598081498453981321742215493367719285367880739881232858424483579281808273469861719596446436314590189292769983411477766191893913977169631957119875579349136281305614481492627652228773582533749827479470392290418282606328213423505081606327326950919142474377406876983181726838449637678370182097567691844978839461869335547061918662244654358814933363523370138558543578475271269926118895717140681845717178521771681353149993455459551220206971133049635893135497481920396479213777241697894795468323709339819431822088195627988822434862598280371891909798387280649159403773906389792360241666391790608158817693188434403840366597399819721040931962105644618015442814739615834439304681273963455194291457602314987027721112833286704410981623921463347334359012567022888434397021502448178062295264674176797858733094823789744825145992654524771821326745213373528074353832374223493027732084537598856537521054829641638518841492809758153750344737394190426384243489985176144225406151937230249872519096772449708471698183468575708578753072843241485511427470266121138374992266995910956445831447732683936539369494258435282245347294707039723385517353896684527437568216585099646688539055973897293496675726668657519479923252481931816449569256805174767041728833158117707258408045368733194753349484723337571310794397422794167942481451289241978318905494369649116656596655703110858811885550184038615959538465638543898255827226177347261290485071281187736080733926634264976858261234113475987643785814341382203263833330758853782554737864873556311799923740368487391745295952421860621090423224627885566622444356786847737920566680399922816588917232427653247386524642641782485450912565777372293783711632473498741952798923202198408326897891793616867687845624304325278779823092538363747325199875892841945013567810759762712419105662944027376875112811669874377312702866952136225418745250663651411616383996382457289621215732382016943963454344922617384421302614983915944171991360652528891048504957685323779576426640467997373319665623192881962791161923787044874660295473358015754895885715746566239563387229939725693212268198801213348687604089817839958088346943629812146243234514182284486598735579393612914564764044296830917910691685265448938859505726269344672165196850193581501388329092647367395840577355812854389591762397663281449044175835104194843974441578567743506112613330153912437973821563868648584839477370983243425499426497161333505090837938982772698124454812308999778070243119132639109818963639688626362247251039326040566094829789315214546982918385978673221971805271973015252455481272854390371793742094111224761412746581439167554273112831747619739641182885124198811724648520475071532275968045387822472069992078392059128062848712349276433953756295867867619476387654334421332393715072741139337164571989402851529630266964138266751933288324186184471444354056511218177166483213214742292678179381386160968157292433282281494133245236691333711276932075752171924553711027259559582660515662533335523827209567941945472094143469293046505522278543675086575023593676125640382775562375725924665892375250935775637420936284629311849186501515953716463775126334969750216567319789827161977887972749557395687446826129301565365427112173968154154543774988752158775759659379944626895829873485132948707389875728353535676013401514828156102120592148514679428790728314731511126243496389152248305724633578408997857023472335191123103570221568626370441946697371683452451743222924348065613020922972771192665366844726157328556073633318458565516578473515637624249647961536666759954384698172421246409843253313652076137049827740616419403888795524375384728752326537377837733543671558988484708785607060446765731244769482697617472720372777824627957578532826193724598321484679718592712611394773114139428073204478191217904121342962346713949334933426671799923150593151313917409592533360316734363629527173417828779328505420775599638165154817636357454226387565114420902786673496632660933260808266936863143718264027176796327289249967108293652446865423548583972298258127371154988990782376683786177412964147638134164323729410338461488559247446213111603959366252917131336367872918821961979229547073269124978126655519341958408799945828159815512369654436738420641179617163121972947830996271334653533154234685152049574158152368965566914184746490165123874160678421859667734067639536784572545575336011705771846858188762428915473162449580737327124342434949395731852914313480638051812258717259439394693944709757527111627391395179217017161222689212388799234830972071955491579444832877741718379698366551689126821531266523741998439561496831609858816660281711841676433379867331758278673287277256461068897543709893248591121850129050746547231349928966173129972220635797391386806426659669345864252998699869148114902714693845564025781491807150789098835731448353844656594779425736969830365842455969147119584567161560631928731140482564277523168532319384327620121829763334205770631126609053705492527698772230601767279419275232203212752282259532647163255289706750939881791745386985536327298095234748802641874986656996175533556920431227676331873874689720224579763612854378288526393795851641223348557770135352687245962973467015334245968939407550141671714173453879302736897427347472316284466120145585938121938338835783767041623463337814251893806228525481135411309834507122158469983972837140822881577312882757939451888664464193932016605923697933358637374452756045324471325658929482976111116716112175577093398891166327718610366955608058104650744216587260709286292988846675842839849094733954746391971239427528295962875333513643825852239988376524811177976195809439594785893783554484641753766168118984736274127023863579909310483460724180119557973723776642731287607584193599698081114391399111425494337710252041926339214885723965436912809415581563796380233658541484383337548063241261224196746255257047433489824722328376103378298944693296686853442062415451411235115666777278982913602712321254645066223962945588331251528531885870375272858413989845128432711544595896319786963426801021562838358185704921147815909245694868364334248668105470475989707262359994897954235475511646644937731555625793914627953026756051702241567014578177285436138948977086227591811948817829447195424522957348835074282212745352819270221810891459575974997552191666743747151969487926589436663395274230646583137978618976346560867842383214562543384757162547177149117783605780675634229765974179757067493799291591264758539698591145196010924878825563531422834885875688149365359296137529896560439136631916641621581835482689197551399674191551472597799356619532316899499116476486919195811964816036158526644967961918665387819462939867564245619889267778353824974639934828351010543325891670502135999782354966365676128623206398859742158336536842758172579029801548298381667658878210139268865358679997145272624767372260163379144617445254494125774799665172332933113646546521207082177374795464775595472560267961624897497113189341386643499615258495174021943567407875374688124562137816447696336530121937932728972955341849284992412932338285553129545769862140804152349031949675946223887798871033384225771577172974506523113646144736605389559635193914744816595793417318457353526591122970448928818549234683136941737538348764638468445864903647126451284472794831467929387460995047988317687895854393884443175395756026355258926326148278443133142073387114904822449029657094589218854468172184731216503167313683755386673539355120399956463496133557801136633884286231844511961134873883597364304486632575284270787651293250254343463578627769508571477775506963159462656472191636157976694311883567222366697273884728642523669722484482108392224812562816202327913294192940151712821868755241508064596134191850556256175962997013825294155663523489935596476125187745109189984587442828308257454545281124898934688044374570881340453926531491478780555075216385978124786587964967769520998991456689754014399540977242514470642393278051462749597311112829689863517473665453169358248726524714211197585339622394852832828567671612627564806997296440345425693721271645365043133069531846696195292940582631284472869844913966197946404149444373778778906954101619567835987514208765476835953480537796792643853382191194287065818034314437645428331136959199334777899147747823452584249029647947802790237521753431764449592356727674423180236150201347834065652793362436384666424523936483107580619184789352612271943155537551624623466094191059959269746429904451724184973787235354576973432573949118874815586459553371782630647437728353135546502315403820491880119846796648292077204658354491102437936694307610862823439838176165689370134433221227306744882030149510553813465094344526581966827310124867483172872044421767454838113655157483967356544894366947686576126016845684976188401842341670173641482013549272447159228997356015733094661443641496762950324715973920671162966166282443569413465116752448881913667436115129649853789876148343781016266564857254573636837977759514539264345762966852607928519841739090713581892828737712241139994773219130902668751113981535133440375281968980785394176564492090793732748586603059898958415163804963862943704775967350338299606899218041575492415966926076424995672226312514723117242293406190807778632051385622747967335254558771613856205838578641638852557051324973593697477156455438149729915225865271277292223442911930386139336329489218837913562569295536514530316865793121917399733459818894452665998791212640558333896823973536552864637579328385789332907365923944965674543772568232946517326778189773242225452276791467335219988813975290876654755836633579432946246055845765572889336525488848214185995218726617388095252355399821156743164281966269909987556387726342787363822631722942532974203833997571689516317932213445162626846877524623414831959953117443178948363739255534779015126554767155167422748076839890103567774598123358207259506999802096541837561851554565881535277568602921358937487836932918375864206338648571913881683424402664916664577924807518308119461226355535546621862216349724318053229922211671355572579157937427776469206577818458381121698840129280363647294815747492597784619887953417889599551298147958939777755619611738468398636921157894582978691647335886605885322452245222919523674495575561792189149539344996441650398367856776276558212628745777529347392061989820569988221364575622713353668180697479985433908840124871689589259116746587176185627220222524906933934048905194505488339866944837228594149181233137467786469260819817526776662952309372741916312792558639931091173459893293856777569033851290191136443762505599567392212795898129932818124290389711979572221285284840403782826529927226266390807354953919393623363054187972341893461720688364624573941169177639278979501647243387576421792183343666841452178017482324668523313531991935641273945170495910723235729169649197635589317877559661131852179110201974402232545777332185517523162343367359288315376140588644427172405960946568222654989642341292345352689370972449569980735195519515967476152231952314247523345175901596856839179486728925401886633034913676673649331957247597454839948732342866793250373170774";

    
//    std::string number = "2333133121414131402";
    // Create a vector to store the digits
    std::vector<int> digits;

    // Loop through each character in the string
    for (char ch : number) {
        // Convert character to integer and push to the vector
        digits.push_back(ch - '0');
    }

    // Print the elements of the array (vector)
    std::cout << "Array of digits: ";
    std::vector<int> vec;
    std::vector<int> indexes;
    indexes.push_back(0);
    
    int curr = 0;
    for (int i = 0; i < digits.size(); i++) {
        
        indexes.push_back(indexes.back() + digits[i]);
        if (i%2 == 0) {
            for (int j = 0; j < digits[i]; ++j) {
                vec.push_back(curr);
            }
            curr += 1;
        } else {
            for (int j = 0; j < digits[i]; ++j) {
                vec.push_back(-1);
            }
        }
    }
    
    int right = int(digits.size()) - 1;
    if (right % 2 != 0) {
        right -= 1;
    }
    std::vector<int> originalDigits = digits;
    
    while (right >= 0) {
        for (int i = 0; i < digits.size()-1; i++) {
            if (i >= right) { break; }
            if (i%2 == 0) { continue; };
            
            if (digits[i] >= digits[right]) {
                digits[i] -= digits[right];
                
                int start = indexes[i];
                int end = indexes[right];
                
                int num = vec[end];
                for (int k = 0; k < digits[right]; k++) {
                    vec[start] = num;
                    start += 1;
                    vec[end] = -1;
                    end += 1;
                }
                indexes[i] += digits[right];
                break;
            }
        }
        right -= 2;
    }
    
    
    // 2333133121414131402
    for (int value: vec) {
        std::cout << value << " ";
    }

    long long result = 0;
    for (int i = 0; i < vec.size(); i ++) {
        if (vec[i] == -1) { continue; }
        result += vec[i] * i;
    }
    std::cout << " result is : " << result << std::endl;
    return 0;
}




- [x]  Day 10
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using std::vector;

int main() {
    // Open the input file
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC10.txt");
    
    // Check if file is opened successfully
    if (!inputFile) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    // A 2D vector to hold the integer values
    std::vector<std::vector<int>> matrix;

    std::string line;
    // Read each line from the file
    while (std::getline(inputFile, line)) {
        std::vector<int> row;
        
        // Process each character in the line
        for (char ch : line) {
            if (ch == '.') {
                row.push_back(-2); // Change '.' to -1
            } else if (std::isdigit(ch)) {
                row.push_back(ch - '0'); // Convert character to integer
            }
        }

        // Add the row to the matrix
        matrix.push_back(row);
    }

    inputFile.close(); // Close the file

    // Print the resulting 2D vector (matrix)
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    
    
    std::vector<std::pair<int, int>> starts;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == 0) {
                starts.push_back({i, j});
            }
        }
    }
    
    int m = matrix.size();
    int n = matrix[0].size();
    
    std::vector<std::pair<int, int>> directions = {
       {-1, 0},  // Up
       {1, 0},   // Down
       {0, -1},  // Left
       {0, 1}    // Right
   };


        // Create an empty queue
    
    std::queue<std::pair<int, int>> queue;
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    
    
    int result = 0;
    for (const auto& pair: starts) {
        queue.push(pair);
        vector<vector<int>> visited = matrix;
        visited[pair.first][pair.second] = -3;
        
        int score = 0;
        while (queue.size() > 0) {
            
            for(int i = 0; i < queue.size(); i++) {
                
                std::pair<int, int> curr = queue.front();
                queue.pop();
                if (matrix[curr.first][curr.second] == 9) {
                    score += 1;
                }
                
                for (const auto&direct: directions) {
                    int x = curr.first + direct.first;
                    int y = curr.second + direct.second;
    
                    if (isValid(x, y) && matrix[x][y] == matrix[curr.first][curr.second] + 1) {
                        std::cout << "x " << x << " is add to queue.";
                        std::cout << "y " << y << " is add to queue"<< std::endl;
                        queue.push({x, y});
                        visited[x][y] = -3;
                    }
                }
            }
        }
        result += score;
        std::cout << std::endl;
        std::cout << "score is : " << score << std::endl;
        for (const auto& row : visited) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "result is : " << result << std::endl;
    return 0;
}




- [x]  Day 11


Part 1:

#include <iostream>
#include <sstream>
#include <vector>

int main() {
    // The string you want to split
    std::string str = "64599 31 674832 2659361 1 0 8867 321";

    // A vector to store the split elements
    std::vector<long long> vector;

    // Create a stringstream object with the input string
    std::stringstream ss(str);
    int number;

    // Split the string by spaces and insert into the vector
    while (ss >> number) {
        vector.push_back(number);
    }

    // Print the elements in the vector
    std::cout << "Split elements:" << std::endl;
    for (int num : vector) {
        std::cout << num << " ";
    }
    
    
    
    for (int i = 0; i < 25; i++) {
        std::vector<long long> temp;
        for (int j = 0; j < vector.size(); j++) {
            if (vector[j] == 0) {
                temp.push_back(1);
                continue;;
            }
            
            long long number = vector[j];
            int numDigits = (int)log10(number) + 1;
            if (numDigits % 2 == 0) {
                int splitPoint = numDigits / 2;
                int divisor = pow(10, splitPoint);
                long long firstPart = number / divisor;
                long long secondPart = number % divisor;
                temp.push_back(firstPart);
                temp.push_back(secondPart);
                continue;;
            }
            temp.push_back(2024 * vector[j]);
        }
        vector = temp;
    }
    std::cout << "result is : " << vector.size() << std::endl;
    
    return 0;
}


Part 2:   构建了graph 用dictionary，并且每一层进行了压缩。 用不着二维数组，太稀疏了，存储会超；

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

//std::vector<std::vector<long long>> matrix(pow(2, 28), std::vector<long long>(76, 0));
//
//long funcOutOfBound(long long num, int time) {
//    std::vector<long long> vector = {num};
//    long long result = 0;
//    for (int i = 0; i < time; i++) {
//       std::vector<long long> temp;
//       for (int j = 0; j < vector.size(); j++) {
//           if (vector[j] < pow(2, 28) && matrix[vector[j]][i] != 0) {
//               result += matrix[vector[j]][i];
//               continue;
//           }
//
//           if (vector[j] == 0) {
//               temp.push_back(1);
//               continue;;
//           }
//
//           long long number = vector[j];
//           int numDigits = (int)log10(number) + 1;
//           if (numDigits % 2 == 0) {
//               int divisor = pow(10, numDigits / 2);
//               temp.push_back(number / divisor);
//               temp.push_back(number % divisor);
//               continue;;
//           }
//           temp.push_back(2024 * vector[j]);
//       }
//       vector = temp;
//   }
//    return result + vector.size();
//}
//
//
//long func(long long num, int time) {
//
//    if (time == 0) {
//        return 1;
//    }
//
//    if (num == 0) {
//        if (matrix[1][time-1] == 0) {
//            matrix[1][time-1] = func(1, time-1);
//        }
//        return matrix[1][time-1];
//    }
//
//    int digits = (int)log10(num) + 1;
//    if (digits % 2 == 0) {
//        int divisor = pow(10, digits/2);
//        if (matrix[num/divisor][time-1] == 0) {
//            matrix[num/divisor][time-1] = func(num/divisor, time-1);
//        }
//        if (matrix[num%divisor][time-1] == 0) {
//            matrix[num%divisor][time-1] = func(num%divisor, time-1);
//        }
//        return matrix[num/divisor][time-1] + matrix[num % divisor][time-1];
//    }
//
//    if (2024 * num >= pow(2, 28)) {
//        return funcOutOfBound(2024*num, time-1);
//    }
//
//    if (matrix[2024 * num][time-1] == 0) {
//        matrix[2024 * num][time-1] = func(2024 * num, time-1);
//    }
//    return matrix[2024 * num][time-1];
//}



std::vector<long long> func(long long num, std::unordered_map<long long, std::vector<long long>> lookup) {
    
    if (lookup.contains(num)) {
        return lookup[num];
    }
    
    if (num == 0) {
        lookup[0] = {1};
    } else if (std::to_string(num).size()%2 == 0) {
        
        std::string alpha = std::to_string(num);
        int l = int(alpha.size() / 2);
        long long left = std::atoi(alpha.substr(0,l).c_str());
        long long right = std::atoi(alpha.substr(l).c_str());
        lookup[num] = { left, right};
    } else {
        lookup[num] = { num * 2024 };
    }
    return lookup[num];
}



int main() {
    int number;
    
    std::string str = "64599 31 674832 2659361 1 0 8867 321";
    std::stringstream ss(str);
    
    std::vector<int> vector;
    
    while (ss >> number) {
        vector.push_back(number);
    }
    
    
    std::unordered_map<long long, long long> couterMap;
    
    for (long long num: vector) {
        couterMap[num] = 1;
    }
    std::unordered_map<long long, std::vector<long long>> lookup;
    
    for (int k = 0; k < 75; k++) {
        std::unordered_map<long long, long long> tempCouterMap;
        for(const auto&pair: couterMap) {
            std::vector<long long> children = func(pair.first, lookup);
            for (const auto& child: children) {
                tempCouterMap[child] += pair.second;
            }
        }
        couterMap = tempCouterMap;
    }
    
    long long result = 0;
    for (const auto&pair: couterMap) {
        result += pair.second;
    }
    std::cout << "result is : " << result << std::endl;
    return 0;
}
 

- [x] Day 12

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC12.txt");  // Open the file (change the filename as needed)
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::vector<std::vector<char>> data;  // 2D vector to hold the characters
    
    std::string line;
    while (std::getline(file, line)) {  // Read each line from the file
        std::vector<char> row(line.begin(), line.end());  // Convert the line to a vector of characters
        data.push_back(row);  // Add the row to the 2D vector
    }
    
    // Close the file
    file.close();
    
    // Print the 2D vector (just to verify)
    for (const auto& row : data) {
        for (const auto& ch : row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
    
    int m = data.size();
    int n = data[0].size();
        
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n, -1));
    
    
    std::vector<std::pair<int, int>> directions = {
       {-1, 0},  // Up
       {1, 0},   // Down
       {0, -1},  // Left
       {0, 1}    // Right
   };

    std::queue<std::pair<int, int>> queue;
    std::unordered_map<int, int> areaMap;
    std::unordered_map<int, int> periMap;
    
    
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >=0 && y < n;
    };
    
    int curr = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            if (matrix[i][j] == -1) {
                
                queue.push({i, j});
                matrix[i][j] = curr;
                int areaCounter = 0;
                while (queue.size() > 0) {
                    auto node = queue.front();
                    queue.pop();
                    areaCounter += 1;
                    
                    for (auto direct: directions) {
                        int x = node.first + direct.first;
                        int y = node.second + direct.second;
                        
                        if (isValid(x, y) && data[x][y] == data[i][j] && matrix[x][y] != curr) {
                            queue.push({x, y});
                            matrix[x][y] = curr;
                        }
                    }
                }
                areaMap[curr] = areaCounter;
                curr += 1;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            periMap[matrix[i][j]] += 4;
            if (isValid(i, j+1) && matrix[i][j+1] == matrix[i][j]) {
                periMap[matrix[i][j]] -= 2;
            }
            
            if (isValid(i+1, j) && matrix[i+1][j] == matrix[i][j]) {
                periMap[matrix[i][j]] -= 2;
            }
        }
    }
    
    // Print the 2D vector (just to verify)
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "matrix is as following:" << std::endl;
    for (const auto& row : matrix) {
        for (const auto& ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
    
    
    int result = 0;
    for (const auto& pair: areaMap) {
        int prei = periMap[pair.first];
        result += prei * pair.second;
    }
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "area is as following:" << std::endl;
    for (const auto& pair : areaMap) {
        std::cout << "key is: " << pair.first << " area size is: " << pair.second << std::endl;
    }
    
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "peri is as following:" << std::endl;
    for (const auto& pair : periMap) {
        std::cout << "key is: " << pair.first << " peri value is: " << pair.second << std::endl;
    }
    
    std::cout << "result is: " << result << std::endl;
    return 0;
}

Part 2:

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <functional>

int main() {
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC12.txt");  // Open the file (change the filename as needed)
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    std::vector<std::vector<char>> data;  // 2D vector to hold the characters
    std::string line;
    while (std::getline(file, line)) {  // Read each line from the file
        std::vector<char> row(line.begin(), line.end());  // Convert the line to a vector of characters
        data.push_back(row);  // Add the row to the 2D vector
    }
    file.close();
    
    
    
    // Print the 2D vector (just to verify)
    for (const auto& row : data) {
        for (const auto& ch : row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
    
    
    
    int m = int(data.size());
    int n = int(data[0].size());
    
    
    std::vector<std::pair<int, int>> directions = {
       {-1, 0},  // Up
       {1, 0},   // Down
       {0, -1},  // Left
       {0, 1}    // Right
   };
    
    int result = 0;
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n, -1));
    std::queue<std::pair<int, int>> queue;
    std::unordered_map<int, int> areaMap;

    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >=0 && y < n;
    };
    
    
    int curr = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            if (matrix[i][j] == -1) {
                queue.push({i, j});
                matrix[i][j] = curr;
                int areaCounter = 0;
                while (queue.size() > 0) {
                    auto node = queue.front();
                    queue.pop();
                    areaCounter += 1;
                    
                    for (auto direct: directions) {
                        int x = node.first + direct.first;
                        int y = node.second + direct.second;
                        
                        if (isValid(x, y) && data[x][y] == data[i][j] && matrix[x][y] != curr) {
                            queue.push({x, y});
                            matrix[x][y] = curr;
                        }
                    }
                }
                areaMap[curr] = areaCounter;
                curr += 1;
            }
        }
    }
    
    
    std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "area is as following:" << std::endl;
   for (const auto& pair : areaMap) {
       std::cout << "key is: " << pair.first << " area size is: " << pair.second << std::endl;
   }
    
    std::cout << std::endl;
    std::cout << std::endl;
    // Print the 2D vector (just to verify)
    for (const auto& row : matrix) {
        for (const auto& ch : row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }

    
    std::set<int> seen;
    
    std::unordered_map<int, std::set<std::vector<int>>> outsidePeriMap;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            if (seen.contains(matrix[i][j])) { continue; }
            std::set<std::vector<int>> visited;
            
            outsidePeriMap.clear();
            seen.insert(matrix[i][j]);
            
            std::queue<std::pair<int, int>> queue1;
            queue1.push({i, j});
            visited.insert({i, j});
            
            while (queue1.size() > 0) {
                auto node = queue1.front();
                queue1.pop();
            
                for (int k = 0; k < 4; k++) {
                    int x = node.first + directions[k].first;
                    int y = node.second + directions[k].second;
                    
                    if (isValid(x, y)) {
                        if (matrix[x][y] != matrix[i][j]) {
                            if (matrix[i][j] == 4) {
                                std::cout << std::endl;
                            }
                            outsidePeriMap[k].insert({x, y});
                        }
                        
                        if (matrix[x][y] == matrix[i][j] && !visited.contains({x, y})) {
                            queue1.push({x, y});
                            visited.insert({x, y});
                        }
                    } else {
                        if (matrix[i][j] == 4) {
                            std::cout << std::endl;
                        }
                        outsidePeriMap[k].insert({x, y});
                    }
                }
            }
            
            std::cout << " Node is " << matrix[i][j] << std::endl;
            for (auto pair: outsidePeriMap) {
                std::cout << " Direction is " << pair.first << std::endl;
                for (auto item: pair.second) {
                    std::cout << " ( " << item[0] << "," << item[1] << ")";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            
            int peri = 0;
            for (int i = 0; i < 4; i++) {
//                std::set<std::pair<int, int>> nodes;
                std::set<std::vector<int>> nodes = outsidePeriMap[i];
                std::set<std::vector<int>> isVisited;
                std::queue<std::vector<int>> queue;
                for (auto& node: nodes) {
                    if (!isVisited.contains(node)) {
                        queue.push(node);
                        visited.insert(node);
                        peri += 1;
                        while (queue.size() > 0) {
                            std::vector<int> curr = queue.front();
                            queue.pop();
                            
                            for (int k = 0; k < 4; k++) {
                                int x = curr[0] + directions[k].first;
                                int y = curr[1] + directions[k].second;
                                
                                if (nodes.contains({x, y}) && !isVisited.contains({x, y})) {
                                    queue.push({x, y});
                                    isVisited.insert({x, y});
                                }
                            }
                        }
                    }
                }
            }
            std::cout << "area key " << matrix[i][j] << "'s perimeter is " << peri << std::endl;
            result += areaMap[matrix[i][j]] * peri;
        }
    }
    
    std::cout << "result is: " << result << std::endl;
    return 0;
}



- [x] Day 13
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
  
// Struct to hold coordinates
struct Coordinates {
    int x, y;
};

// Function to extract a coordinate (X or Y) from a string like "X+94" or "X=8400"
int extractCoordinate(const std::string& str) {
    std::regex r("[-+]?\\d+");  // Regular expression to match an integer (positive or negative)
    std::smatch match;
    if (std::regex_search(str, match, r)) {
        return std::stoi(match.str(0));  // Convert the matched string to an integer
    }
    return 0;  // Return 0 if no valid number is found
}

int main() {
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC13.txt");  // Replace with the actual file path
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    // Vectors to store the coordinates for Button A, Button B, and Prize
    std::vector<long long> xA, yA, xB, yB, xPrize, yPrize;

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Button A") != std::string::npos) {
            Coordinates buttonA;
            // Read "Button A: X+94, Y+34"
            // Directly extract the X and Y values from the line for Button A
            size_t posX = line.find("X+");
            size_t posY = line.find("Y+");
            if (posX != std::string::npos && posY != std::string::npos) {
                buttonA.x = extractCoordinate(line.substr(posX));
                buttonA.y = extractCoordinate(line.substr(posY));
            } else {
                std::cerr << "Error: Unable to find coordinates in Button A line: " << line << std::endl;
                continue;
            }

            // Read Button B coordinates
            Coordinates buttonB;
            std::getline(file, line);  // Read "Button B: X+22, Y+67"
            posX = line.find("X+");
            posY = line.find("Y+");
            if (posX != std::string::npos && posY != std::string::npos) {
                buttonB.x = extractCoordinate(line.substr(posX));
                buttonB.y = extractCoordinate(line.substr(posY));
            } else {
                std::cerr << "Error: Unable to find coordinates in Button B line: " << line << std::endl;
                continue;
            }

            // Read Prize coordinates
            Coordinates prize;
            std::getline(file, line);  // Read "Prize: X=8400, Y=5400"
            posX = line.find("X=");
            posY = line.find("Y=");
            if (posX != std::string::npos && posY != std::string::npos) {
                prize.x = extractCoordinate(line.substr(posX));
                prize.y = extractCoordinate(line.substr(posY));
            } else {
                std::cerr << "Error: Unable to find coordinates in Prize line: " << line << std::endl;
                continue;
            }

            // Store the values in vectors
            xA.push_back(buttonA.x);
            yA.push_back(buttonA.y);
            xB.push_back(buttonB.x);
            yB.push_back(buttonB.y);
            xPrize.push_back(10000000000000 + prize.x);
            yPrize.push_back(10000000000000 + prize.y);
        }
    }

    
    long long result = 0;
    // Output the coordinates stored in the vectors
    for (size_t i = 0; i < xA.size(); ++i) {
        

        long long detX = xB[i] * yA[i] - xA[i] * yB[i];
        long long detAx = yPrize[i] * xB[i] - xPrize[i] * yB[i];

        // Calculate det(A_y)
        long long detAy = xA[i] * yPrize[i] - yA[i] * xPrize[i];
        long long detY = yB[i] * xA[i] - yA[i] * xB[i];
        // Calculate x and y using Cramer's Rule
        
        if (detAx % detX != 0) { continue; }
        if (detAy % detY != 0) { continue; }
        long long A = detAx / detX;
        long long B = detAy / detY;
        
        if (A>=0 && B>=0) {
//        if (A>=0 && A<100 && B>=0 && B<100) {
            result += 3 * A + 1 * B;
            std::cout << "valid row is: " << i << std::endl;
            std::cout << "press A " << A << " times" << "Press B: " << B << " times" << std::endl;
        }
        
//        std::cout << "Button A " << i + 1 << ": (" << xA[i] << ", " << yA[i] << ")\n";
//        std::cout << "Button B " << i + 1 << ": (" << xB[i] << ", " << yB[i] << ")\n";
//        std::cout << "Prize " << i + 1 << ": (" << xPrize[i] << ", " << yPrize[i] << ")\n";
    }
    std::cout << "result is: " << result << std::endl;
    return 0;
}


- [x]  Day 14  Part 1:
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


using std::cout;   // Only bring 'cout' into scope
using std::endl;   // Only bring 'endl' into scope
using std::vector; // Only bring 'vector' into scope


struct Vector2D {
    int x, y;
};

struct DataPoint {
    Vector2D position;  // Position (p)
    Vector2D velocity;  // Velocity (v)
};

int main() {
    // Open the file containing the data
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC14.txt");

    // Check if the file was successfully opened
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::vector<DataPoint> data;
    std::string line;

    // Read each line from the file
    while (std::getline(inputFile, line)) {
        DataPoint point;
        
        // Parse position (p=0,4)
        size_t posStart = line.find("p=") + 2;
        size_t posEnd = line.find("v=") - 1;
        std::string posStr = line.substr(posStart, posEnd - posStart);
        std::stringstream posStream(posStr);
        char comma; // To discard commas
        posStream >> point.position.y >> comma >> point.position.x;

        // Parse velocity (v=3,-3)
        size_t velStart = line.find("v=") + 2;
        std::string velStr = line.substr(velStart);
        std::stringstream velStream(velStr);
        velStream >> point.velocity.y >> comma >> point.velocity.x;

        // Add the parsed data to the vector
        data.push_back(point);
    }

    // Close the file after reading
    inputFile.close();

    // Iterate through the vector and print position and velocity
    for (const auto& entry : data) {
        std::cout << "Position: (" << entry.position.x << ", " << entry.position.y << "), "
                  << "Velocity: (" << entry.velocity.x << ", " << entry.velocity.y << ")\n";
    }
    
    
    int m = 103;
    int n = 101;
    
    vector<vector<int>> vector(m, std::vector<int>(n, 0));
    
    for (const auto& entry : data) {
        int seconds = 100;
        int x = entry.position.x;
        int y = entry.position.y;
        while (seconds-- >0) {
            x = (m + x + entry.velocity.x) % m;
            y = (n + y + entry.velocity.y) % n;
        }
        vector[x][y]++;
    }
    
    
    for (auto row: vector) {
        for (auto node: row) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    std::vector<int> quadrant;
    
    int sum = 0;
    for (int i = 0; i < m/2; i++) {
        for (int j = 0; j < n/2; j++) {
            sum += vector[i][j];
        }
    }
    quadrant.push_back(sum);
    
    sum = 0;
    for (int i = m/2+1; i < m; i++) {
        for (int j = 0; j < n/2; j++) {
            sum += vector[i][j];
        }
    }
    quadrant.push_back(sum);
    
    sum = 0;
    for (int i = 0; i < m/2; i++) {
        for (int j = n/2+1; j < n; j++) {
            sum += vector[i][j];
        }
    }
    
    quadrant.push_back(sum);
    sum = 0;
    for (int i = m/2+1; i < m; i++) {
        for (int j = n/2+1; j < n; j++) {
            sum += vector[i][j];
        }
    }
    quadrant.push_back(sum);
    
    int result = 1;
    for (auto item: quadrant) {
        cout << "item is: " << item << endl;
        result *= item;
    }
    cout << "result is: " << result << endl;
    return 0;
}

Part 2:
- [x] #include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>


using std::cout;   // Only bring 'cout' into scope
using std::endl;   // Only bring 'endl' into scope
using std::vector; // Only bring 'vector' into scope

class DSU {
public:
    std::vector<int> roots;
    std::vector<int> ranks;

    // Constructor to initialize DSU with n elements
    DSU(int n) {
        // Initialize roots to be each element's own root
        roots.resize(n);
        ranks.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            roots[i] = i;
        }
    }

    // Union operation to combine two sets
    bool unionSets(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);
        
        if (xRoot == yRoot) {
            return false; // They are already in the same set
        }

        // Union by rank: attach the smaller tree under the larger tree
        if (ranks[xRoot] > ranks[yRoot]) {
            roots[yRoot] = xRoot;
        } else if (ranks[xRoot] < ranks[yRoot]) {
            roots[xRoot] = yRoot;
        } else {
            roots[yRoot] = xRoot;  // Arbitrary choice if ranks are equal
            ranks[xRoot] += 1;      // Increment the rank of the new root
        }

        return true;
    }

    // Find operation with path compression
    int find(int current) {
        std::vector<int> path;  // To store the path for compression

        while (roots[current] != current) {
            path.push_back(current);  // Add current node to path
            current = roots[current];
        }

        // Path compression: make each node on the path point directly to the root
        for (int p : path) {
            roots[p] = current;
            ranks[p] = 1;  // Reset rank to 1 for nodes that were compressed
        }

        ranks[current] = 2;  // Mark the root node with a higher rank
        return current;
    }
};



int cluster(std::vector<std::vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int M = int(grid.size());
    int N = int(grid[0].size());
    int count = 0;
    
    DSU dsu(M * N);  // Initialize DSU for the grid with M * N nodes

    // Iterate through each cell in the grid
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == '#') {
                int current = i * N + j;
                count++;
                if (j + 1 < N && grid[i][j + 1] == '#') {
                    if (dsu.unionSets(current, i * N + (j + 1))) {
                        count--;
                    }
                }
                if (i + 1 < M && grid[i + 1][j] == '#') {
                    if (dsu.unionSets(current, (i + 1) * N + j)) {
                        count--;
                    }
                }
            }
        }
    }
    return count;
}


struct Vector2D {
    int x, y;
    
    bool operator<(const Vector2D& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<Vector2D> {
        size_t operator()(const Vector2D& v) const {
            // Combine the hash values of x and y using a simple hash function
            size_t hash_x = hash<int>{}(v.x);  // Hash the x value
            size_t hash_y = hash<int>{}(v.y);  // Hash the y value

            // Combine the two hash values (you can improve this combination)
            return hash_x ^ (hash_y << 1);  // XOR hash_x with shifted hash_y
        }
    };
}


struct DataPoint {
    Vector2D position;  // Position (p)
    Vector2D velocity;  // Velocity (v)
};

int main() {
    // Open the file containing the data
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC14.txt");

    // Check if the file was successfully opened
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::vector<DataPoint> data;
    std::string line;

    // Read each line from the file
    while (std::getline(inputFile, line)) {
        DataPoint point;
        
        // Parse position (p=0,4)
        size_t posStart = line.find("p=") + 2;
        size_t posEnd = line.find("v=") - 1;
        std::string posStr = line.substr(posStart, posEnd - posStart);
        std::stringstream posStream(posStr);
        char comma; // To discard commas
        posStream >> point.position.y >> comma >> point.position.x;

        // Parse velocity (v=3,-3)
        size_t velStart = line.find("v=") + 2;
        std::string velStr = line.substr(velStart);
        std::stringstream velStream(velStr);
        velStream >> point.velocity.y >> comma >> point.velocity.x;

        // Add the parsed data to the vector
        data.push_back(point);
    }

    // Close the file after reading
    inputFile.close();

    // Iterate through the vector and print position and velocity
//    for (const auto& entry : data) {
//        std::cout << "Position: (" << entry.position.x << ", " << entry.position.y << "), "
//                  << "Velocity: (" << entry.velocity.x << ", " << entry.velocity.y << ")\n";
//    }
//
    int m = 103;
    int n = 101;
    int seconds = 0;
    while (seconds++ < 10000) {
        std::vector<std::vector<char>> graph(m, std::vector<char>(n, '.'));
        for (int i = 0; i<data.size(); i++) {
            DataPoint entry = data[i];
            int x = entry.position.x;
            int y = entry.position.y;
            
            x = (m + x + entry.velocity.x) % m;
            y = (n + y + entry.velocity.y) % n;
            
            data[i] = DataPoint(Vector2D(x, y), Vector2D(entry.velocity.x, entry.velocity.y));
        }
        
        for (int i = 0; i<data.size(); i++) {
            DataPoint entry = data[i];
            int x = entry.position.x;
            int y = entry.position.y;
            graph[x][y] = '#';
        }
        
        int numberOfCluster = cluster(graph);
        
        
        if (numberOfCluster < 200) {
            cout << "second is : " << seconds <<endl;
            for (auto row: graph) {
                for (auto item: row) {
                    cout << item << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    return 0;
}
  

in line with : 在一条直线上
12-2：外轮廓， 相同临近，方向 group

