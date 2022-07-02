#include <vector>
#include <iostream>
using namespace std;

struct S_Itype
{
    string func3, name;
    int rs1, rs2d, immediate;
};
S_Itype ADDI32 = { "000", "ADDI" };
S_Itype SLTI32 = { "010", "SLTI" };
S_Itype SLTIU32 = { "011", "SLTIU" };
S_Itype XORI32 = { "100", "XORI" };
S_Itype ORI32 = { "110", "ORI" };
S_Itype ANDI32 = { "111", "ANDI" };
S_Itype SLLI32 = { "001", "SLLI" };
S_Itype SRLI32 = { "101", "SRLI" };
S_Itype SRAI32 = { "101", "SRAI" };
S_Itype LB32 = { "000", "LB" };
S_Itype LH32 = { "001", "LH" };
S_Itype LW32 = { "010", "LW" };
S_Itype LBU32 = { "100", "LBU" };
S_Itype LHU32 = { "101", "LHU" };

S_Itype SB32 = { "000", "SB" };
S_Itype SH32 = { "001", "SH" };
S_Itype SW32 = { "010", "SW" };

vector<S_Itype> Immediate32 = { ADDI32, SLTI32, SLTIU32, XORI32, ORI32, ANDI32, SLLI32, SRLI32, SRAI32 };
vector<S_Itype> Load32 = { LB32, LH32, LW32, LBU32, LHU32 };
vector<S_Itype> Store32 = { SB32, SH32, SW32 };