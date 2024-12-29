#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <sstream>
#include <random>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <tuple>

// Helper function to print the output and also copy to clipboard (similar to `pr()` in Python)
void pr(const std::string& s) {
    std::cout << s << std::endl;
    // Clipboard functionality can be added using external libraries like "pyperclip" in C++ if needed
}

// Gate operation function (AND, OR, XOR)
int doOp(int v1, int v2, const std::string& op) {
    if (op == "AND") {
        return v1 & v2;
    } else if (op == "OR") {
        return v1 | v2;
    } else if (op == "XOR") {
        return v1 ^ v2;
    } else {
        assert(false && "Unknown operation");
    }
}

// Swap two gates in the gate list
void swapGates(std::vector<std::vector<std::string>>& gates, std::vector<std::string> sequence, int i1, int i2) {
    
    std::string a = sequence[i1];
    std::string b = sequence[i2];
    
    int index1 = 0;
    int index2 = 0;
    for (int i = 0; i < gates.size(); i++) {
        if (gates[i][4] == sequence[i1]) {
            index1 = i;
        }
        if (gates[i][4] == sequence[i2]) {
            index2 = i;
        }
    }
    std::swap(gates[index1][4], gates[index2][4]);
}

int gatesIndex(std::vector<std::vector<std::string>> gates, std::string str) {
    for (int i = 0; i < gates.size(); i++) {
        if (gates[i][4] == str) {
            return i;
        }
    }
    assert("index error");
    return 0;
}

// Simulate the circuit and compute the wrong bits
int generateLeastUntrustedZGateDigit(const std::vector<std::vector<std::string>>& gates, const std::string& values) {
    std::set<int> WRONG;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, pow(2, 46));
    
    for (int _ = 0; _ < 10; ++_) {
        // Random X and Y values
        int X = dis(gen);
        int Y = dis(gen);

        std::unordered_map<std::string, int> V;
        
        std::istringstream valuesStream(values);
        std::string line;
        while (std::getline(valuesStream, line)) {
            size_t colonPos = line.find(": ");
            std::string name = line.substr(0, colonPos);
            int value = std::stoi(line.substr(colonPos + 2));
            int idx = std::stoi(name.substr(1));

            if (name[0] == 'x') {
                V[name] = (X >> idx) & 1;
            } else if (name[0] == 'y') {
                V[name] = (Y >> idx) & 1;
            } else {
                assert(false && "Unknown variable name");
            }
        }

        bool changed;
        do {
            changed = false;
            for (size_t i = 0; i < gates.size(); ++i) {
                const auto& gate = gates[i];
                const std::string& n1 = gate[0];
                const std::string& op = gate[1];
                const std::string& n2 = gate[2];
                const std::string& n3 = gate[4];
                
                if (V.find(n1) != V.end() && V.find(n2) != V.end() && V.find(n3) == V.end()) {
                    V[n3] = doOp(V[n1], V[n2], op);
                    changed = true;
                }
            }
        } while (changed);

        // Calculate the result Z
        int Z = 0;
        for (const auto& kv : V) {
            if (kv.first[0] == 'z') {
                int idx = std::stoi(kv.first.substr(1));
                Z += pow(2, idx) * kv.second;
            }
        }

        // Compare bits of Z with expected value C (sum of X and Y)
        int C = X + Y;
        for (int bit = 0; bit < 46; ++bit) {
            int zbit = (Z >> bit) & 1;
            int correct_bit = (C >> bit) & 1;
            if (zbit != correct_bit) {
                WRONG.insert(bit);
            }
        }
    }

    return *WRONG.begin();
}

// Verify the second answer (run the final circuit and calculate the output)
void runVerify(const std::vector<std::vector<std::string>>& gates, const std::string& values) {
    std::unordered_map<std::string, int> V;
    std::istringstream valuesStream(values);
    
    std::string line;
    while (std::getline(valuesStream, line)) {
        size_t colonPos = line.find(": ");
        std::string name = line.substr(0, colonPos);
        int value = std::stoi(line.substr(colonPos + 2));

        if (name[0] == 'x') {
            V[name] = value;
        } else if (name[0] == 'y') {
            V[name] = value;
        } else {
            assert(false && "Unknown variable name");
        }
    }

    bool changed;
    do {
        changed = false;
        for (size_t i = 0; i < gates.size(); ++i) {
            const auto& gate = gates[i];
            const std::string& n1 = gate[0];
            const std::string& op = gate[1];
            const std::string& n2 = gate[2];
            const std::string& n3 = gate[4];

            if (V.find(n1) != V.end() && V.find(n2) != V.end() && V.find(n3) == V.end()) {
                V[n3] = doOp(V[n1], V[n2], op);
                changed = true;
            }
        }
    } while (changed);

    // Calculate the result Z
    long Z = 0;
    for (const auto& kv : V) {
        if (kv.first[0] == 'z') {
            int idx = std::stoi(kv.first.substr(1));
            Z += pow(2, idx) * kv.second;
        }
    }
    std::cout << "First Answer is " << Z << std::endl;
}

std::unordered_map<std::string, std::vector<std::string>> dependencyMap;


std::set<std::string> fetchDependency(
    std::string zString,
    std::unordered_map<std::string, std::vector<std::string>> dependencyMap
) {
    std::set<std::string> set;
    std::queue<std::string> queue;
    queue.push(zString);
    
    while (queue.size()>0) {
        std::string curr = queue.front();
        queue.pop();
        set.insert(curr);
        // no cycle ganrented, no need to check seen
        for (auto value: dependencyMap[curr]) {
            queue.push(value);
        }
    }
    return set;
}



int main(int argc, char* argv[]) {
    // Read input file

    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC24.txt");
    if (!file.is_open()) {
        assert("file open error.");
    }
    
    std::string D((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Split the input into values and gates
    size_t delimPos = D.find("\n\n");
    std::string values = D.substr(0, delimPos);
    std::string gatesStr = D.substr(delimPos + 2);

    // Parse gates
    std::vector<std::vector<std::string>> gates;
    std::istringstream gatesStream(gatesStr);
    std::string gateLine;
    while (std::getline(gatesStream, gateLine)) {
        std::istringstream lineStream(gateLine);
        std::vector<std::string> gate;
        std::string word;
        while (lineStream >> word) {
            gate.push_back(word);
        }
        gates.push_back(gate);
    }
    file.close();
    
    std::unordered_map<std::string, std::vector<std::string>> dependencyMap;
    for(auto gate: gates) {
        dependencyMap[gate[4]] = {gate[0], gate[2]};
    }
    

    // Run verification
    runVerify(gates, values);

    std::set<std::string> allGates;
    for (auto gate: gates) {
        allGates.insert(gate[0]);
        allGates.insert(gate[2]);
        allGates.insert(gate[4]);
    }
    // Run the error detection and optimization
    
    
    std::set<std::string> trustedDependency;
    std::set<std::string> speciousDependency;
    
    std::set<std::string> OUT;
    
    int lastScore = 0;
    jump: while (OUT.size() < 8) {
        
        
        int score = generateLeastUntrustedZGateDigit(gates, values);
        std::string zFormatted = std::format("Z{:02}", score-1);
        std::set<std::string> tempTrusted = fetchDependency(zFormatted, dependencyMap);
        trustedDependency.insert(tempTrusted.begin(), tempTrusted.end());
        
        for (auto item: allGates) {
            if (!trustedDependency.contains(item)) {
                speciousDependency.insert(item);
            }
        }
        
        std::vector<std::string> sequence(speciousDependency.begin(), speciousDependency.end());
        for (size_t i0 = 0; i0 < sequence.size(); ++i0) {
            for (size_t i1 = i0+1; i1 < sequence.size(); ++i1) {
                if (i0 == i1) { continue; }
                swapGates(gates, sequence, i0, i1);
                int newScore = generateLeastUntrustedZGateDigit(gates, values);
                if (lastScore == 0 || newScore > lastScore) {
                    lastScore = newScore;
                    OUT.insert(sequence[i0]);
                    OUT.insert(sequence[i1]);
                    goto jump;
                }
                swapGates(gates, sequence, i0, i1);
            }
        }
    }

    std::string outStr;
    for (const auto& out : OUT) {
        outStr += out + ",";
    }
    if (!outStr.empty()) {
        outStr.pop_back(); // Remove last comma
    }

    std::cout << "Second Answer is " << outStr << std::endl;

    // Verify the final output
    std::cout << "Verify Second Answer is " << std::endl;
    runVerify(gates, values);

    return 0;
}
