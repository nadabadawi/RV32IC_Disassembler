#pragma once
#include <vector>
#include <iostream>
using namespace std;

// Index of vector is funct3 value
vector<string> Immediate32 = {"ADDI", "SLLI", "SLTI", "SLTIU", "XORI", "SRLI", "ORI", "ANDI", "SRAI"};
vector<string> Load32 = {"LB", "LH", "LW", "UNKNOWN", "LBU", "LHU"};
vector<string> Store32 = {"SB", "SH", "SW"};
vector<string> Branch32 = {"BEQ", "BNE", "UNKNOWN", "UNKNOWN", "BLT", "BGE", "BLTU", "BGEU"};
vector<string> Env = {"ECALL", "EBREAK", "FENCE"};
// Index of vector is funct3 value except for the last two instructions
// 0->7: fun7 = 0 and 8->9: fun7 = 1
vector<string> Register32 = {"ADD", "SLL", "SLT", "SLTU", "XOR", "SRL", "OR", "AND", "SUB", "SRA"};
vector<string> LoadStore16 = {"C.LW", "C.SW"};
vector<string> Immediate16 = {"C.SRLI", "C.SRAI", "C.ANDI", "C.ADDI"};
vector<string> Arithmetic16 = {"C.SUB", "C.XOR", "C.OR", "C.AND"};