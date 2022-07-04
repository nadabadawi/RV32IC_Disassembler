#include <iostream>
#include <vector>
#include <bitset>
#include "RB.h"

using namespace std;


string ABI[32] = { "zero", "ra", "sp", "gp", "tp", "t0","t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3" ,"a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };
string CABI[8] = { "s0", "s1", "a0", "a1",  "a2", "a3", "a4", "a5" };



void IW32(unsigned int IW);
void IW16(unsigned int IW);


int main()
{
	unsigned int add_test = 0x90A2;
	unsigned int test_32 = 0x04848463;
	IW16(add_test);
	IW32(test_32);
	system("pause");
	return 0;
}

void IW32(unsigned int IW)
{
	unsigned int opcode, rd, funct3, rs1, rs2, funct7;
	unsigned int immediate_12, immediate_10to5, immediate_4to1, immediate_11;

	opcode = IW & 0x7F; //Last 7 bits
	funct3 = (IW >> 12) & 0x7; //3 bits
	rs1 = (IW >> 15) & 0x1F; //5 bits
	rs2 = (IW >> 20) & 0x1F; //5 bits
	rd = (IW >> 7) & 0x1F; //5 bits
	funct7 = (IW >> 25) & 0x7F; // 7 bits
	immediate_12 = (IW >> 31) & 0x1; //1 bit
	immediate_10to5 = (IW >> 25) & 0x3F; //6 bits
	immediate_4to1 = (IW >> 8) & 0x1F; //4 bits
	immediate_11 = (IW >> 7) & 0x1; //1 bit
	unsigned int B_imm = (immediate_12 << 12) | (immediate_11 << 11) | (immediate_10to5 << 5) | (immediate_4to1 << 1) | 0x0;
	cout << "Test: " << opcode << " " << funct3 << " " << rs1 << " " << rs2 << " " << immediate_12 << endl;
	switch (opcode)
	{
	case (51):
	{
		if (funct7 == 0)
			cout << Register32[funct3] << " " << ABI[rd] << ", " << ABI[rs2] << ABI[rs2] << "\n";
		else
		{
			if (funct3 == 0)
			{
				cout << Register32[8] << " " << ABI[rd] << ", " << ABI[rs2] << ABI[rs2] << "\n";
			}
			else if (funct3 == 5)
			{
				cout << Register32[9] << " " << ABI[rd] << ", " << ABI[rs2] << ABI[rs2] << "\n";
			}
		}
		break;
	}
	case (99):
	{
		cout << Branch32[funct3] << " " << ABI[rs1] << ", " << ABI[rs2] << ", " << B_imm << endl;
		break;
	}

	default:
		cout << "Unkown Instruction \n";
	}

}
void IW16(unsigned int IW)
{
	unsigned int opcode, ADD_rs2, ADD_rd_rs1, funct4, A_rs2, funct2, A_rd_rs1, funct6;

	opcode = IW & 0x3; //Last 2 bits
	ADD_rs2 = (IW >> 2) & 0x1F; //5 bits
	ADD_rd_rs1 = (IW >> 7) & 0x1F; //5 bits
	funct4 = (IW >> 12) & 0xF; // 4 bits

	A_rs2 = (IW >> 2) & 0x7; // 3 bits
	funct2 = (IW >> 5) & 0x3; // 2 bits
	A_rd_rs1 = (IW >> 7) & 0x7; //3 bits
	funct6 = (IW >> 10) & 0x3F; // 6 bits

	if (opcode == 1 && funct6 == 35)
		cout << Arithmetic16[funct2] << " " << CABI[A_rd_rs1] << ", " << CABI[A_rd_rs1] << ", " << CABI[A_rs2] << endl;
	else if (opcode == 2 && funct4 == 9 && ADD_rs2 != 0 && ADD_rd_rs1 != 0)
		cout << "C.ADD " << ABI[ADD_rd_rs1] << ", " << ABI[ADD_rd_rs1] << ", " << ABI[ADD_rs2] << endl;
	else
		cout << "Unkown instruction \n";
}




