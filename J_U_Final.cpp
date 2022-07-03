//  J_U_Final.cpp
//  Dissasembler
//  Created by Nermien Elassy on 03/07/2022.
#include "J_U_Final.hpp"
#include <iostream>
#include <vector>
#include <bitset>
//#include "Instructions32bits.cpp"
//#include "I32.h"
//#include "Instructions16bits.cpp"
using namespace std;

//Notes: 1- Change immediate values to hexadecimals.

string ABI[32] = { "zero", "ra", "sp", "gp", "tp", "t0","t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3" ,"a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };
string CABI[8] = { "s0", "s1", "a0", "a1",  "a2", "a3", "a4", "a5" };

//vector<pair<string, Rtype >> opcodes = { "0010011","0000011", "0100011" };
//vector<Rtype>
//vector<string> opcodes = {"0010011","0000011", "0100011"};

void InstDec16bit(unsigned int IW);
void InstDec32bit(unsigned int IW);


int main()
{
    //Testing 32 bits IW:
    /*unsigned int bin = 0xC6520F23;
    unsigned int lhu = 0x00545403;
    unsigned int test2 = 0x40535293;
    InstDec32bit(lhu);*/
    unsigned int bin2 = 0x48C0; //--> C.LW //0xC8C0 --> C.SW
    unsigned int addi = 0x315;
    /*bitset<16> x(bin2);
    cout << x << endl << endl;*/
    InstDec16bit(addi);
    system("pause");
    return 0;
}



void InstDec32bit(unsigned int IW)
{
    unsigned int rd, rs1, rs2, funct3, funct7, opcode, S_imm_temp, J_imm_temp;
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
    U_imm = ((IW >> 12) & (0xfffff));
    J_imm_temp = ((((IW >> 21) & (0x3ff) )  | //1:10
              ((IW >> 20) & (0b1)   )  | //11
              ((IW >> 12) & (0xff)  )  | //12:19
              ((IW >> 30) & (0b1)  )) << 1 ) | 0x0; //20
    J_imm = J_imm_temp/2;
    cout << "Test: " << opcode << " " << funct3 << " " << rs1 << " " << rs2 << " " << S_imm << endl;
    //funct3 is the index of each vector (based on opcode)
    cout << "Test2: " << opcode << "\n\n";
    switch (opcode)
    {
    case (35):
        cout << Store32[funct3] << " " << ABI[rs2] << ", " << dec << S_imm << "(" << ABI[rs1] << ")\n";
        break;
    case (19): //IF FUNCT3 = 101 THEN CHECK IMM[11:5] != 0 THEN INDEX = 8
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
    case (3):
        cout << Load32[funct3] << " " << ABI[rd] << ", " << int(I_imm) << "(" << ABI[rs1] << ")\n";
        break;
    case (55):
            cout << "LUI"
                   << ABI[rd] << ", " << hex << U_imm << endl;
    
    case (23):
            cout << "AUIPC"
                   << ABI[rd] << ", " << hex << U_imm << endl;
    case (111):
            cout << "JAL"
                   << ABI[rd] << ", " << hex << J_imm << endl;
        default:
        cout << "Unkown Instruction \n";
    }

    // � inst[31] � inst[30:25] inst[24:21] inst[20]
    //I_imm = ((IW >> 20) & 0x7FF) | (((IW >> 31) ? 0xFFFFF800 : 0x0));
}


void InstDec16bit(unsigned int IW)
{
    //unsigned int rd, rs1, rs2, funct3, funct7, opcode, S_imm_temp;
    //unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
    //unsigned int address;

    unsigned int opcode, rs1_3, rs1_5, rd, S_imm, I_imm, J_imm, U_imm, funct3, funct2;
    //unsigned int instPC = pc - 4;
    unsigned int seg1, seg2, temp2, temp6;


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
    J_imm =  ((((
                      ( ( (IW >> 3) & (0x7) )   << 1 )|
                      ( ( (IW >> 12) & (0x1) )  << 4 )|
                      ( ( (IW >> 2) & (0x1)  )  << 5 )|
                      ( ( (IW >> 7) & (0x1)  )  << 6 )|
                      ( ( (IW >> 6) & (0x1)  )  << 7 )|
                      ( ( (IW >> 10) & (0x3) )  << 8 )|
                      ( ( (IW >> 9)  & (0x1) ) << 10 )|
                      ( ( (IW >> 11) & (0x1) ) << 11 ))) << 1) | 0x0);
    U_imm = ((
              ( ( (IW >> 2) & (0b11111) )|
              ( ( (IW >> 12) & (0b1)    ) ))) << 12) | 0x0;


    //cout << "Test: " << opcode << " " << funct3 << " " << rs1 << " " << rs2 << " " << S_imm << endl;
    ////funct3 is the index of each vector (based on opcode)
    //cout << "Test2: " << opcode << "\n\n";

    cout << "funct3: " << funct3 << endl;
    switch (opcode)
    {
    case (0):
        cout << LoadStore16[(funct3 - 2) / 4] << " " << CABI[rd] << ", " << dec << S_imm << "(" << CABI[rs1_3] << ")\n";
        break;
    case 1: //IF FUNCT3 = 101 THEN CHECK IMM[11:5] != 0 THEN INDEX = 8
    {
        if (funct3 == 0)
            cout << Immediate16[3] << " " << ABI[rs1_5] << ", " << ABI[rs1_5] << ", " << int(I_imm) << endl; //Since the register is 5 bits
        if (funct3 == 4)
            cout << Immediate16[funct2] << " " << CABI[rs1_3] << ", " << CABI[rs1_3] << ", " << int(I_imm) << endl;
        if (funct3 == 1)
            cout << "C.JAL" <<" "<< int(J_imm) << endl;
        else
            cout << "C.LUI" <<" " << ABI[rs1_5] << "," << int(U_imm) << endl;
        break;
    }
    case 2:
        cout << "C.SLLI" << " " << CABI[rs1_3] << ", " << CABI[rs1_3] << ", " << int(I_imm) << endl;
        break;
    
    default:
        cout << "Unkown Instruction \n";
    }
}
