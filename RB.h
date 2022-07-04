#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;


//Index of vector is funct3 value except for the last two instructions
//0->7: fun7 = 0 and 8->9: fun7 = 1
vector<string> Register32 = { "ADD", "SLL", "SLT", "SLTU", "XOR", "SRL", "OR","AND","SUB","SRA" };

//Index of vector is funct3 value
vector<string> Branch32 = { "BEQ","BNE","UNKNOWN","UNKNOWN","BLT","BGE","BLTU","BGEU" };

//Index of vector is func3
vector<string> Arithmetic16 = { "C.SUB","C.XOR", "C.OR", "C.AND" };

