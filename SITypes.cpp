#include <iostream>
#include <vector>
#include "I32.h"
using namespace std;

string ABI[32] = { "zero", "ra", "sp", "gp", "tp", "t0","t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3" ,"a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };

void InstDec16bit(string IW);
void InstDec32bit(unsigned int IW);


int main()
{
	unsigned int bin = 0xC6520F23;
	unsigned int lhu = 0x00545403;
	unsigned int test2 = 0x40535293;
	InstDec32bit(lhu);
	system("pause");
	return 0;
}



void InstDec32bit(unsigned int IW)
{
	unsigned int rd, rs1, rs2, funct3, funct7, opcode, S_imm_temp;
	unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
	//unsigned int address;

	//unsigned int instPC = pc - 4;
	opcode = IW & 0x0000007F; //Last 7 bits
	S_imm = (IW >> 7) & 0x0000001F; //5 bits
	rd = (IW >> 7) & 0x1F; //5 bits
	funct3 = (IW >> 12) & 0x00000007; //3 bits
	rs1 = (IW >> 15) & 0x0000001F; //5 bits
	rs2 = (IW >> 20) & 0x0000001F; //5 bits
	I_imm = (IW >> 20) & 0xFFF; //12 bits
	S_imm_temp = (IW >> 25) & 0x0000007F; //First 7 bits
	S_imm = (S_imm_temp << 5) | S_imm;
	cout << "Test: " << opcode << " " << funct3 << " " << rs1 << " " << rs2 << " " << S_imm << endl;
	//funct3 is the index of each vector (based on opcode)
	cout << "Test2: " << opcode << "\n\n";
	switch (opcode)
	{
	case (35):
		cout << Store32[funct3] << " " << ABI[rs2] << ", " << dec << S_imm << "(" << ABI[rs1] << ")\n";
		break;
	case 19: //IF FUNCT3 = 101 THEN CHECK IMM[11:5] != 0 THEN INDEX = 8
	{
		if (funct3 == 1 || funct3 == 5)
		{
			I_imm = rs2;
			if (S_imm_temp != 0)
				funct3 = 0x8;
		}
		cout << Immediate32[funct3] << " " << ABI[rd] << ", " << ABI[rs1] << ", " << int(I_imm) << endl;
		break;
	}
	case 3:
		cout << Load32[funct3] << " " << ABI[rd] << ", " << int(I_imm) << "(" << ABI[rs1] << ")\n";
		break;
	default:
		cout << "Unkown Instruction \n";
	}

	// — inst[31] — inst[30:25] inst[24:21] inst[20]
	//I_imm = ((IW >> 20) & 0x7FF) | (((IW >> 31) ? 0xFFFFF800 : 0x0));
}


void InstDec16bit(string IW)
{

}