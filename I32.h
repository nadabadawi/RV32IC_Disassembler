#pragma once
#include <vector>
#include <iostream>
using namespace std;
//Remove funct3 from struct!!
//We do not need a struct!! 
//Save names in vector to display;
struct S_Itype
{
    unsigned int func3;
    string name;
    int rs1, rs2d, immediate;
};
S_Itype ADDI32 = { 000, "ADDI" }; //0 
S_Itype SLTI32 = { 010, "SLTI" }; //2
S_Itype SLTIU32 = { 011, "SLTIU" }; //3
S_Itype XORI32 = { 100, "XORI" }; //4
S_Itype ORI32 = { 110, "ORI" }; //6
S_Itype ANDI32 = { 111, "ANDI" }; //7
S_Itype SLLI32 = { 001, "SLLI" }; //1
S_Itype SRLI32 = { 101, "SRLI" }; //5   --> IF FUNCT3 = 101 THEN CHECK IMM [11:5] != 0 THEN INDEX = 8
S_Itype SRAI32 = { 101, "SRAI" }; //5  HERE

//Different Opcode:
S_Itype LB32 = { 000, "LB" }; //0
S_Itype LH32 = { 001, "LH" }; //1
S_Itype LW32 = { 010, "LW" }; //2
S_Itype LBU32 = { 100, "LBU" }; //4
S_Itype LHU32 = { 101, "LHU" }; //5
S_Itype dummy; //3

S_Itype SB32 = { 000, "SB" }; //0
S_Itype SH32 = { 001, "SH" }; //1
S_Itype SW32 = { 010, "SW" }; //2


//Index of vector is funct3 value
vector<S_Itype> Immediate32 = { ADDI32, SLLI32, SLTI32, SLTIU32, XORI32, SRLI32, ORI32, ANDI32 , SRAI32 };
vector<S_Itype> Load32 = { LB32, LH32, LW32, dummy, LBU32, LHU32 };
vector<S_Itype> Store32 = { SB32, SH32, SW32 };
