//
//  18.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

Day 18


Part 1:

#include <iostream>
#include <fstream>
#include <sstream>  // for std::istringstream
#include <vector>
#include <queue>
#include <utility>  // for std::pair
using namespace std;

int main() {
    // Open the file
    ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC18.txt");

    // Check if the file was opened successfully
    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return 1;  // Exit the program with error code
    }

    vector<pair<int, int>> coordinates;
    string line;

    // Read the file line by line
    while (getline(inputFile, line)) {
        // Use stringstream to extract x and y values from the line
        istringstream ss(line);
        int x, y;
        char comma;
        
        // Extract x and y from the current line
        if (ss >> x >> comma >>  y) {
            coordinates.push_back({x, y});
        } else {
            // Print error message with the line that caused the failure
            cerr << "Error reading coordinates from line: \"" << line << "\"" << endl;
        }
    }

    // Close the file
    inputFile.close();

//     Print the coordinates
    cout << "Read coordinates from file:" << endl;
    for (const auto& coord : coordinates) {
        cout << "(" << coord.first << ", " << coord.second << ")" << endl;
    }
    
    int n = 71;
    vector<vector<string>> matrix(n, vector<string>(n, "."));
    
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    int k = 0;
    for (int i = 0; i < 1024; i++) {
        matrix[coordinates[i].second][coordinates[i].first] = "#";
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    
    int sr = 0;
    int sc = 0;
    int er = n-1;
    int ec = n-1;
    
    int direction[4][2] = {
        {-1, 0},  // Up
        {1, 0},   // Down
        {0, -1},  // Left
        {0, 1}    // Right
    };
    
    queue<vector<int>> queue;
    queue.push({sr, sc});
    
    vector<vector<bool>> isVisited(n, vector<bool>(n, false));
    isVisited[sr][sc] = true;
    
    auto isValid = [&n](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < n;
    };
    
    int steps = 0;
    
    while (queue.size() > 0) {
        steps += 1;
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            
            vector<int> curr = queue.front();
            queue.pop();
            
            
            for(auto direct: direction) {
                int r = curr[0] + direct[0];
                int c = curr[1] + direct[1];
                
                if (r == er && c == ec) {
                    goto final;
                }
                if (isValid(r, c) && !isVisited[r][c] && matrix[r][c] == ".") {
                    queue.push({r, c});
                    isVisited[r][c] = true;
                    matrix[r][c] = std::to_string(steps);
                }
            }
        }
    }
    
  
    final:cout << "result is: " << steps << endl;
    
    
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    

    return 0;
}
  Part 2:  trial and binary search. (not full solution) 


#include <iostream>
#include <fstream>
#include <sstream>  // for std::istringstream
#include <vector>
#include <queue>
#include <utility>  // for std::pair
using namespace std;

int main() {
    // Open the file
    ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC18.txt");

    // Check if the file was opened successfully
    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return 1;  // Exit the program with error code
    }

    vector<pair<int, int>> coordinates;
    string line;

    // Read the file line by line
    while (getline(inputFile, line)) {
        // Use stringstream to extract x and y values from the line
        istringstream ss(line);
        int x, y;
        char comma;
        
        // Extract x and y from the current line
        if (ss >> x >> comma >>  y) {
            coordinates.push_back({x, y});
        } else {
            // Print error message with the line that caused the failure
            cerr << "Error reading coordinates from line: \"" << line << "\"" << endl;
        }
    }

    inputFile.close();


//    cout << "Read coordinates from file:" << endl;
//    for (const auto& coord : coordinates) {
//        cout << "(" << coord.first << ", " << coord.second << ")" << endl;
//    }
    
    int n = 71;
    int start = 0;
    int end = coordinates.size()-1;
    
    vector<int> result = {0, 0};
    while (start + 1 < end) {
        
        int mid = (start + end) / 2;
        
        vector<vector<string>> matrix(n, vector<string>(n, "."));
    
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                cout << matrix[i][j] << " ";
//            }
//            cout << endl;
//        }
        for (int i = 0; i < mid; i++) {
            matrix[coordinates[i].second][coordinates[i].first] = "#";
        }
        int sr = 0;
        int sc = 0;
        int er = n-1;
        int ec = n-1;
        
        int direction[4][2] = {
            {-1, 0},  // Up
            {1, 0},   // Down
            {0, -1},  // Left
            {0, 1}    // Right
        };
        
        queue<vector<int>> queue;
        queue.push({sr, sc});
        
        vector<vector<bool>> isVisited(n, vector<bool>(n, false));
        isVisited[sr][sc] = true;
        
        auto isValid = [&n](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < n;
        };
        
        bool hasExited = false;
        while (queue.size() > 0) {
            int size = int(queue.size());
            for (int i = 0; i < size; i++) {
                vector<int> curr = queue.front();
                queue.pop();
    
                for(auto direct: direction) {
                    int r = curr[0] + direct[0];
                    int c = curr[1] + direct[1];
                    
                    if (r == er && c == ec) {
                        hasExited = true;
                    }
                    if (isValid(r, c) && !isVisited[r][c] && matrix[r][c] == ".") {
                        queue.push({r, c});
                        isVisited[r][c] = true;
                    }
                }
            }
        }
        final: if (hasExited) {
            start = mid;
        } else {
            end = mid;
        }
    }

    cout << "result is: " << coordinates[start].first << "," << coordinates[start].second << endl;
    return 0;
}
