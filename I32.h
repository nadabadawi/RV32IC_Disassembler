#pragma once
#include <vector>
#include <iostream>
using namespace std;


//Index of vector is funct3 value
vector<string> Immediate32 = { "ADDI", "SLLI", "SLTI", "SLTIU", "XORI", "SRLI", "ORI", "ANDI" , "SRAI" };
vector<string> Load32 = { "LB", "LH", "LW", "UNKNOWN", "LBU", "LHU" };
vector<string> Store32 = { "SB", "SH", "SW" };
