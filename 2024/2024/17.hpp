//
//  17.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

Day 17 - XX  #include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Registers {
    long A;
    long B;
    long C;
};

long get_combo_value(int literal, const Registers& regs) {
    switch (literal) {
        case 0: return 0;  // Literal 0
        case 1: return 1;  // Literal 1
        case 2: return 2;  // Literal 2
        case 3: return 3;  // Literal 3
        case 4: return regs.A;  // Value of register A
        case 5: return regs.B;  // Value of register B
        case 6: return regs.C;  // Value of register C
        default:
            std::cerr << "Invalid combo operand: " << literal << std::endl;
            return 0;  // Default return value in case of an invalid operand (shouldn't happen)
    }
}

// adv instruction (opcode 0) - Division
void adv(Registers& regs, int literal) {
    long divisor = pow(2, get_combo_value(literal, regs));  // 2 raised to the power of combo
    regs.A = regs.A / divisor;    // Division with truncation
}

// bxl instruction (opcode 1) - Bitwise XOR with register B
void bxl(Registers& regs, int literal) {
    regs.B = regs.B ^ literal;    // Bitwise XOR with B
}

// bst instruction (opcode 2) - Modulo 8 and store in B
void bst(Registers& regs, int literal) {
    regs.B = get_combo_value(literal, regs) % 8;  // Only keep the lowest 3 bits (modulo 8)
}

// jnz instruction (opcode 3) - Jump if A != 0
bool jnz(Registers& regs, long literal) {
    if (regs.A != 0) {
        return true;  // Return true to indicate jump
    }
    return false;  // No jump
}

// bxc instruction (opcode 4) - XOR B with C
void bxc(Registers& regs, int /*literal*/) {
    regs.B = regs.B ^ regs.C;  // XOR B with C (literal operand is ignored)
}

// out instruction (opcode 5) - Output modulo 8 of combo
void out(Registers& regs, int literal) {
    std::cout << (get_combo_value(literal, regs) % 8) << ",";  // Output the result modulo 8
}

// bdv instruction (opcode 6) - Division, result stored in B
void bdv(Registers& regs, int literal) {
    long divisor = pow(2, get_combo_value(literal, regs));
    regs.B = regs.A / divisor;  // Store result in B
}

// cdv instruction (opcode 7) - Division, result stored in C
void cdv(Registers& regs, int literal) {
    long divisor = pow(2, get_combo_value(literal, regs));
    regs.C = regs.A / divisor;  // Store result in C
}


// Function to execute an instruction given opcode and operand(s)
int execute_instruction(int opcode, Registers& regs, int operand, std::unordered_map<int, int> map, int curretIndex) {
    switch (opcode) {
        case 0:  // adv instruction
            adv(regs, operand);
            break;
        case 1:  // bxl instruction
            bxl(regs, operand);
            break;
        case 2:  // bst instruction
            bst(regs, operand);
            break;
        case 3:  // jnz instruction
            if (jnz(regs, operand)) {
                return map[operand];
            }
            break;
        case 4:  // bxc instruction
            bxc(regs, operand);
            break;
        case 5:  // out instruction
            out(regs, operand);
            break;
        case 6:  // bdv instruction
            bdv(regs, operand);
            break;
        case 7:  // cdv instruction
            cdv(regs, operand);
            break;
        default:
            std::cerr << "Unknown opcode: " << opcode << std::endl;
    }
    return curretIndex + 2;
}




int main() {
    // Open the input file
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC17.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Variables to store registers and program
    Registers regs;
   
    std::vector<int> program;

    std::string line;

    // Reading registers (A, B, C)
    std::getline(inputFile, line);  // Read "Register A: 729"
    std::istringstream(line.substr(12)) >> regs.A;  // Extract 729
    
    std::getline(inputFile, line);  // Read "Register B: 0"
    std::istringstream(line.substr(12)) >> regs.B;  // Extract 0

    std::getline(inputFile, line);  // Read "Register C: 0"
    std::istringstream(line.substr(12)) >> regs.C;  // Extract 0

    // Skip the empty line
    std::getline(inputFile, line);

    // Read program (the list of instructions)
    std::getline(inputFile, line);  // Read "Program: 0,1,5,4,3,0"
    std::istringstream programStream(line.substr(9));  // Extract "0,1,5,4,3,0"
    
    int instruction;
    char comma;
    while (programStream >> instruction) {
        program.push_back(instruction);
        programStream >> comma;  // Skip the comma
    }

    // Close the file
    inputFile.close();

    // Output the registers and program to verify
    std::cout << "Register A: " << regs.A << std::endl;
    std::cout << "Register B: " << regs.B << std::endl;
    std::cout << "Register C: " << regs.C << std::endl;

    std::cout << "Program: ";
    for (int i : program) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    
    
    

//    Registers testRegex;
//    testRegex.A = 2024;
////    testRegex.B = 2024;
////    testRegex.C = 43690;
//    std::vector<int> testProgram = {0,1,5,4,3,0};
//
//    regs = testRegex;
//    program = testProgram;
//
    std::unordered_map<int, int> map;
    
    for (int index = 0; index < program.size(); index += 2) {
        map[index] = index;
    }
    
    int i = 0;
    
    while (i < program.size()) {

        i = execute_instruction(program[i], regs, program[i+1], map, i);
    }
//
//    std::cout  << std::endl;
//    std::cout << "Test result is as following>" << std::endl;
//
//    std::cout << "A is " << regs.A << std::endl;
//    std::cout << "B is " << regs.B << std::endl;
//    std::cout << "C is " << regs.C << std::endl;
    return 0;
}


    Part 2::


import re
import sys


with open(sys.argv[1], "r") as f:
    a, b, c, *program = list(map(int, re.findall(r"\d+", f.read())))


def computer(a: int, b: int = 0, c: int = 0) -> list[int]:

    def combo(val: int) -> int:
        assert val != 7, "Invalid combo value"
        if val <= 3:
            return val
        reg_map = {4: a, 5: b, 6: c}
        return reg_map[val]

    output = []
    ip = 0
    while ip < len(program):
        opcode = program[ip]
        operand = program[ip + 1]
        match opcode:
            case 0:  # adv
                a = a >> combo(operand)
            case 1:  # bxl
                b = b ^ operand
            case 2:  # bst
                b = combo(operand) % 8
            case 3:  # jnz
                if a != 0:
                    ip = operand
                    continue
            case 4:  # bxc
                b = b ^ c
            case 5:  # out
                output.append(combo(operand) % 8)
            case 6:  # bdv
                b = a >> combo(operand)
            case 7:  # cdv
                c = a >> combo(operand)
        ip += 2
    return output


part1 = ",".join(map(str, computer(a, b, c)))
print(f"Part 1: {part1}")


candidates = [0]
for l in range(len(program)):
    next_candidates = []
    for val in candidates:
        for i in range(8):
            target = (val << 3) + i
            if computer(target) == program[-l - 1 :]:
                next_candidates.append(target)
    candidates = next_candidates

part2 = min(candidates)
print(f"Part 2: {part2}")


