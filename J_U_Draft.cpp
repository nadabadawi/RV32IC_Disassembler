#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <iomanip>
/*
    Add a file called: Instruction.h and add to it all the declarations of the
    structs.
    Each new instruction that you want to add, you just create its struct and
    inherit from the base Instruction and define the two functions:
        - void Prepare(uint32_t bitStream)
        - PrintInstruction();
*/
using namespace std;
struct Instruction
{
    virtual void Prepare(uint32_t bitStream) = 0;
    virtual void PrintInstruction() = 0;
    uint32_t rd, rs1, rs2;
    int32_t imm;
};
//J-type

// JAL rd, label(imm)
struct Jal : public Instruction
{
    void Prepare(uint32_t bitStream) override
    {
        rd =  (bitStream >> 7) & (0b11111);
        imm = ((   ((bitStream >> 21) & (0x3ff) )  | //1:10
                   ((bitStream >> 20) & (0b1)   )  | //11
                   ((bitStream >> 12) & (0xff)  )  | //12:19
                   ((bitStream >> 30) & (0b1)   )) << 1 ) | 0x0; //20
        //immediate is represented in half words
        imm /=2;
    }
    void PrintInstruction() override
    {
           cout << "jal"
                  << "x" << rd << ", " << hex << imm << endl;
    }
};
//U-type

// LUI rd, imm(hexdecimal)
struct LUI : public Instruction
{
    void Prepare(uint32_t bitStream) override
    {
        rd = (bitStream >> 7) & (0b11111);
        imm = ((bitStream >> 12) & (0xfffff));
    }

    void PrintInstruction() override
    {
        cout << "lui"
               << "x" << rd << ", " << hex << imm << endl;
    }
};
// AUIPC rd, imm(hexdecimal)
struct AUIPC : public Instruction
{
    void Prepare(uint32_t bitStream) override
    {
        rd = (bitStream >> 7) & (0b11111);
        imm = ((bitStream >> 12) & (0xfffff));
    }

    void PrintInstruction() override
    {
        cout << "AUIPC"
               << "x" << rd << ", " << hex << imm << endl;
    }
};

//ECALL
struct ECALL : public Instruction
{
    void PrintInstruction() override
    {
        cout << "ecall"<<endl;
    }
};

//EBREAK
//Needs a way to check for the last 12 bits
struct EBREAK : public Instruction
{
    void PrintInstruction() override
    {
        cout << "ebreak"<<endl;
    }
};
//"HERE IS THE START OF THE COMPRESSED INSTRUCTIONS"

//J-type
/*
struct CJ : public Instruction
{
    void Prepare(uint32_t bitStream) override
    {
       
        imm = 0 |
         ( ( (bitStream >> 3) & (0x7) )   << 1 )|
         ( ( (bitStream >> 12) & (0x1) )  << 4 )|
         ( ( (bitStream >> 2) & (0x1)  )  << 5 )|
         ( ( (bitStream >> 7) & (0x1)  )  << 6 )|
         ( ( (bitStream >> 6) & (0x1)  )  << 7 )|
         ( ( (bitStream >> 10) & (0x3) )  << 8 )|
         ( ( (bitStream >> 9)  & (0x1) ) << 10 )|
         ( ( (bitStream >> 11) & (0x1) ) << 11 );
        //immediate is represented in half words
        //imm /=2;
    }
    void PrintInstruction() override
    {
           cout << "jal"
                  << "x0" << ", " << hex << imm << endl;
    }
};
 */
struct CJAL : public Instruction
{
    void Prepare(uint32_t bitStream) override
    {
       
        imm = ((((
         ( ( (bitStream >> 3) & (0x7) )   << 1 )|
         ( ( (bitStream >> 12) & (0x1) )  << 4 )|
         ( ( (bitStream >> 2) & (0x1)  )  << 5 )|
         ( ( (bitStream >> 7) & (0x1)  )  << 6 )|
         ( ( (bitStream >> 6) & (0x1)  )  << 7 )|
         ( ( (bitStream >> 10) & (0x3) )  << 8 )|
         ( ( (bitStream >> 9)  & (0x1) ) << 10 )|
         ( ( (bitStream >> 11) & (0x1) ) << 11 ))) << 1) | 0x0);
        //immediate is represented in half words
        //imm /=2;
    }
    void PrintInstruction() override
    {
           cout << "jal"
                  << "x1" << ", " << hex << imm << endl;
    }
};
struct CLUI : public Instruction
{
    void Prepare(uint32_t bitStream) override
    {
        
        rd = (bitStream >> 7) & (0b11111);
        
        imm = ((
         ( ( (bitStream >> 2) & (0b11111) )|
         ( ( (bitStream >> 12) & (0b1)    ) ))) << 12) | 0x0;
        //immediate is represented in half words
        //imm /=2;
    }
    void PrintInstruction() override
    {
           cout << "lui" <<"x"
                  << rd << ", " << hex << imm << endl;
    }
};

// Function retunrs pointer to an instruction
// Finds out the type of the instruction by
// examining the opcode and funct3 and func7

Instruction *
DecodeType(int bitStream)
{
    uint32_t opcode = bitStream & 0x7f;
    uint32_t func3 = bitStream & 1;
    switch (opcode)
    {
    case //JAL_OPCODE:
    {
        Instruction *jal = new Jal();

        jal->Prepare(bitStream);
        return jal;
    }
    break;

    case ADD_OPCODE:
        Instruction *add = new Add();
        add->Prepare(bitStream);
        return add;
        break;
    }
}

int main(int argc, char const *argv[])
{
    std::vector<Instruction *> instructions;
    int pc = 0;
    while (true)
    {
        uint32_t instWord = 0; // Coming from the memory
        pc += 2;

        instructions.push_back(DecodeType(instWord));
        // Some way to break;
    }

    for (auto &inst : instructions)
    {
        inst->PrintInstruction();
    }
    return 0;
}

