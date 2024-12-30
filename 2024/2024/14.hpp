//
//  14.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

- [x] Day 14; Part 2 - Union Find 帮助搜索  #include <iostream>
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
