#include <vector>
#include <iostream>
using namespace std;

struct S_Itype
{
    string func3, name;
    int rs1, rs2d, immediate;
};
S_Itype ADDI16 = { "00001", "C.ADDI" };
S_Itype SLLI16 = { "00010", "C.SLLI" };

// FUNCT2 + FUNCT3 + OP
S_Itype ANDI16 = { "1010001", "C.ANDI" };
S_Itype SRLI16 = { "0010001", "C.SRLI" };
S_Itype SRAI16 = { "0110001", "C.SRAI" };

S_Itype LW16 = { "01000", "C.LW" };

S_Itype SW16 = { "11000", "C.SW" }; // funct3 + op

vector<S_Itype> Immediate16 = { ADDI16, ANDI16, SLLI16, SRLI16, SRAI16 };
vector<S_Itype> Load16 = { LW16 };
vector<S_Itype> Store16 = { SW16 };