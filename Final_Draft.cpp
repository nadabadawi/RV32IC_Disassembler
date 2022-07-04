#include <iostream>
#include <vector>
#include <bitset>
//#include "Instructions32bits.cpp"
#include "Instructions.h"
#include <fstream>
#include <iomanip>
//#include "Instructions16bits.cpp"
using namespace std;

//Notes: 1- Change immediate values to hexadecimals.

string ABI[32] = { "zero", "ra", "sp", "gp", "tp", "t0","t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3" ,"a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };
string CABI[8] = { "s0", "s1", "a0", "a1",  "a2", "a3", "a4", "a5" };

//Utility Functions:
void printPrefix(unsigned int instA, unsigned int instW);
void emitError(string s);
void Read16bits(unsigned int& instWord);
//Main Algorithm:
void InstDec16bit(unsigned int IW);
void InstDec32bit(unsigned int IW);

char memory[8 * 1024];
unsigned int pc = 0x0;


int main(int argc, char* argv[])
{

	unsigned int instWord = 0;
	unsigned int instWord_second_part = 0;
	ifstream inFile;
	ofstream outFile;

	if (argc < 2) emitError("use: rvcdiss <machine_code_file_name>\n");

	inFile.open(argv[1], ios::in | ios::binary | ios::ate);

	if (inFile.is_open())
	{
		int fsize = inFile.tellg();
		int count = 0;
		//cout << "Size: " << fsize;
		inFile.seekg(0, inFile.beg);
		if (!inFile.read((char*)memory, fsize)) emitError("Cannot read from input file\n");

		while (true) {
			Read16bits(instWord);
			count++;
			if ((instWord & 0b11) == 3)
			{
				Read16bits(instWord_second_part);
				instWord = (instWord_second_part << 16) | instWord;
				count++;
				InstDec32bit(instWord);
			}
			else
				InstDec16bit(instWord);

				if (count == fsize) break;
		}
	}
	else emitError("Cannot access input file\n");
}

/*int main()
{
	//Testing 32 bits IW:
	/*unsigned int bin = 0xC6520F23;
	unsigned int lhu = 0x00545403;
	unsigned int test2 = 0x40535293;
	InstDec32bit(lhu);
	unsigned int bin2 = 0x48C0; //--> C.LW //0xC8C0 --> C.SW
	unsigned int addi = 0x315;
	/*bitset<16> x(bin2);
	cout << x << endl << endl;
	InstDec16bit(addi);
	system("pause");
	return 0;
}*/



void InstDec32bit(unsigned int IW)
{
	unsigned int rd, rs1, rs2, funct3, opcode;
	unsigned int I_imm, S_imm, S_imm_temp;
	//unsigned int address;
	unsigned int  funct7;
	unsigned int immediate_12, immediate_10to5, immediate_4to1, immediate_11, J_imm_temp, U_imm, J_imm;

	unsigned int instPC = pc - 4;

	opcode = IW & 0x0000007F; //Last 7 bits
	//S_imm = (IW >> 7) & 0x0000001F; //5 bits
	rd = (IW >> 7) & 0x1F; //5 bits //rd for I-Type and imm[4:0] for S-Type
	funct3 = (IW >> 12) & 0x00000007; //3 bits
	rs1 = (IW >> 15) & 0x0000001F; //5 bits
	rs2 = (IW >> 20) & 0x0000001F; //5 bits
	I_imm = (IW >> 20) & 0xFFF; //12 bits
	S_imm_temp = (IW >> 25) & 0x0000007F; //First 7 bits
	S_imm = (S_imm_temp << 5) | rd;

	U_imm = ((IW >> 12) & (0xfffff));
	J_imm_temp = ((((IW >> 21) & (0x3ff)) | //1:10
		((IW >> 20) & (0b1)) | //11
		((IW >> 12) & (0xff)) | //12:19
		((IW >> 30) & (0b1))) << 1) | 0x0; //20
	J_imm = J_imm_temp / 2;

	funct7 = (IW >> 25) & 0x7F; // 7 bits
	immediate_12 = (IW >> 31) & 0x1; //1 bit
	immediate_10to5 = (IW >> 25) & 0x3F; //6 bits
	immediate_4to1 = (IW >> 8) & 0x1F; //4 bits
	immediate_11 = (IW >> 7) & 0x1; //1 bit
	unsigned int B_imm = (immediate_12 << 12) | (immediate_11 << 11) | (immediate_10to5 << 5) | (immediate_4to1 << 1) | 0x0;

	//cout << "Test: " << opcode << " " << funct3 << " " << rs1 << " " << rs2 << " " << S_imm << endl;

	//funct3 is the index of each vector (based on opcode)
	printPrefix(instPC, IW);

	switch (opcode)
	{
	case 35:
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
	case 103:
		cout << "JALR " << ABI[rd] << ", " << ABI[rs1] << ", " << I_imm;
	case 55:
		cout << "LUI" << ABI[rd] << ", " << hex << U_imm << endl;
	case 23:
		cout << "AUIPC" << ABI[rd] << ", " << hex << U_imm << endl;
	case 111:
		cout << "JAL " << ABI[rd] << ", " << hex << J_imm << endl;
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
void InstDec16bit(unsigned int IW)
{

	unsigned int opcode, rs1_3, rs1_5, rd, S_imm, I_imm, J_imm, U_imm, funct3, funct2;
	unsigned int seg1, seg2, temp2, temp6;
	unsigned int  ADD_rs2, ADD_rd_rs1, funct4, A_rs2, funct2_1, A_rd_rs1, funct6;

	unsigned int instPC = pc - 2;

	opcode = IW & 0x0003; //Last 2 bits
	rd = (IW >> 2) & 0x0007; //3 bits
	temp6 = (IW >> 5) & 0x1; //1 bit
	temp2 = (IW >> 6) & 0x1; //1 bit
	I_imm = (IW >> 2) & 0x1F; //5 bits
	rs1_3 = (IW >> 7) & 0x7; // 3 bits
	rs1_5 = (IW >> 7) & 0x1F; // 5 bits
	seg2 = (IW >> 12) & 0x1; //1 bit
	funct2 = (IW >> 10) & 0x3; //2 bits of funct2;
	seg1 = (IW >> 10) & 0x7; //3 bits (part of imm in load/store)
	funct3 = (IW >> 13) & 0x7; //3 bits
	S_imm = (temp6 << 6) | (seg1 << 3) | (temp2 << 2) | 0x0;
	I_imm = (seg2 << 5) | I_imm;
	J_imm = ((((
		(((IW >> 3) & (0x7)) << 1) |
		(((IW >> 12) & (0x1)) << 4) |
		(((IW >> 2) & (0x1)) << 5) |
		(((IW >> 7) & (0x1)) << 6) |
		(((IW >> 6) & (0x1)) << 7) |
		(((IW >> 10) & (0x3)) << 8) |
		(((IW >> 9) & (0x1)) << 10) |
		(((IW >> 11) & (0x1)) << 11))) << 1) | 0x0);
	U_imm = ((
		(((IW >> 2) & (0b11111)) |
			(((IW >> 12) & (0b1))))) << 12) | 0x0;

	ADD_rs2 = (IW >> 2) & 0x1F; //5 bits
	funct4 = (IW >> 12) & 0xF; // 4 bits
	funct6 = (IW >> 10) & 0x3F; // 6 bits;
	/*rd*/
	A_rs2 = (IW >> 2) & 0x7; // 3 bits
	funct2_1 = (IW >> 5) & 0x3; // 2 bits
	A_rd_rs1 = (IW >> 7) & 0x7; //3 bits
	/*rs1_5*/
	ADD_rd_rs1 = (IW >> 7) & 0x1F; //5 bits

	printPrefix(instPC, IW);

	//cout << "Test: " << opcode << " " << funct3 << " " << rs1 << " " << rs2 << " " << S_imm << endl;
	////funct3 is the index of each vector (based on opcode)

	cout << "funct3: " << funct3 << endl;
	switch (opcode)
	{
	case 0:
		cout << LoadStore16[(funct3 - 2) / 4] << " " << CABI[rd] << ", " << dec << S_imm << "(" << CABI[rs1_3] << ")\n";
		break;
	case 1: //IF FUNCT3 = 101 THEN CHECK IMM[11:5] != 0 THEN INDEX = 8
	{
		if (funct3 == 0)
			cout << Immediate16[3] << " " << ABI[rs1_5] << ", " << ABI[rs1_5] << ", " << int(I_imm) << endl; //Since the register is 5 bits
		else if (funct3 == 4)
			cout << Immediate16[funct2] << " " << CABI[rs1_3] << ", " << CABI[rs1_3] << ", " << int(I_imm) << endl;
		else if (funct3 == 1)
			cout << "C.JAL " << int(J_imm) << endl;
		else if (funct6 == 35)
			cout << Arithmetic16[funct2_1] << " " << CABI[A_rd_rs1] << ", " << CABI[A_rd_rs1] << ", " << CABI[A_rs2] << endl;
		else
			cout << "C.LUI " << ABI[rs1_5] << "," << int(U_imm) << endl;
		break;
	}
	case 2:
		if (funct3 == 0)
			cout << "C.SLLI " << ABI[rs1_5] << ", " << ABI[rs1_5] << ", " << int(I_imm) << endl;
		else if (funct3 == 4)
			cout << "C.JALR ra, " << ABI[rs1_5] << endl;
		else if (funct4 == 9)
			cout << "C.ADD " << ABI[ADD_rd_rs1] << ", " << ABI[ADD_rd_rs1] << ", " << ABI[ADD_rs2] << endl;
		break;
	default:
		cout << "Unkown Instruction \n";
	}
}

void printPrefix(unsigned int instA, unsigned int instW)
{
	cout << "0x" << hex << std::setfill('0') << std::setw(8) << instA << "\t0x" << std::setw(8) << instW<<" ";
}
void emitError(string s)
{
	cout << s;
	exit(0);
}
void Read16bits(unsigned int& instWord)
{
	instWord = (unsigned char)memory[pc] |
		(((unsigned char)memory[pc + 1]) << 8);
	pc += 2;
}