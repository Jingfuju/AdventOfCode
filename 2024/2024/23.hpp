//
//  23.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

Day 23   #include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

void pr(const string& s) {
    cout << s << endl;
}

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(int argc, char* argv[]) {
    
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC23.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    
    unordered_map<string, unordered_set<string>> map;
    
    std::string line;
    while (getline(inputFile, line)) {
        auto parts = split(line, '-');
        string a = parts[0], b = parts[1];
        map[a].insert(b);
        map[b].insert(a);
    }
    inputFile.close();
    
    
    
    vector<string> vector;
    for (const auto& entry : map) {
        vector.push_back(entry.first);
    }

    sort(vector.begin(), vector.end());

    // Part 1: Count triangles where one node starts with 't'
    int p1 = 0;
    for (size_t i = 0; i < vector.size(); ++i) {
        for (size_t j = i + 1; j < vector.size(); ++j) {
            for (size_t k = j + 1; k < vector.size(); ++k) {
                
                string a = vector[i], b = vector[j], c = vector[k];
                if (map[a].count(b) && map[a].count(c) && map[b].count(c)) {
                    if (a[0] == 't' || b[0] == 't' || c[0] == 't') {
                        ++p1;
                    }
                }
            }
        }
    }

    pr(to_string(p1));

    // Part 2: Find the largest clique
    random_device rd;
    mt19937 randomNumberGenerator(rd());
    
    std::vector<string> best;

    for (int t = 0; t < 1000; ++t) {
        shuffle(vector.begin(), vector.end(), randomNumberGenerator);

        std::vector<string> clique;
        for (const auto& x : vector) {
            bool ok = true;
            for (const auto& y : clique) {
                if (map[x].count(y) == 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) { clique.push_back(x);}
        }

        if (best.empty() || clique.size() > best.size()) {
            best = clique;
        }
    }

    sort(best.begin(), best.end());
    
    for (auto item: best) {
        std::cout << item << ",";
    }
    return 0;
}
