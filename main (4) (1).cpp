#include <iostream>
#include <string>
#include <bitset>
#include <vector>

enum InstructionType
{
	ADDI,
	ADD,
};
/*
	Add a file called: Instruction.h and add to it all the declarations of the
	structs.
	Each new instruction that you want to add, you just create its struct and
	inherit from the base Instruction and define the two functions:
		- void Prepare(uint32_t bitStream)
		- PrintInstruction();
*/
struct Instruction
{
	virtual void Prepare(uint32_t bitStream) = 0;
	virtual void PrintInstruction() = 0;
	InstructionType type;
	std::string name;
	uint32_t rd, rs1, rs2;
	int32_t imm;
};

struct Jal : public Instruction
{
	void Prepare(uint32_t bitStream) override
	{
		imm = 0 | ((((0x3ff << 21) & bitStream) << 1) |
				   (((0x1 << 19) & bitStream) << 11) |
				   (((0xff << 11) & bitStream) << 12) |
				   (((0x1 << 20) & bitStream) << 20));

		uint32_t mask = 0b11111 << 7;

		rd = bitStream & mask;
	}

	void PrintInstruction() override
	{
		std::cout << "JAL "
				  << "x" << rd << ", " << imm << std::endl;
	}
};

struct Add : public Instruction
{
	void Prepare(uint32_t bitStream) override
	{
	}

	void PrintInstruction() override
	{
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
	case JAL_OPCODE:
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

// Jal JalInstruction32(uint32_t bitStream)
// {
// 	Jal inst;
// 	uint32_t mask = 0b11111 << 7;

// 	inst.rd = bitStream & mask;

// 	inst.offset = 0 | ((((0x3ff << 21) & bitStream) << 1) |
// 					   (((0x1 << 19) & bitStream) << 11) |
// 					   (((0xff << 11) & bitStream) << 12) |
// 					   (((0x1 << 20) & bitStream) << 20));
// 	inst.offset /= 2;

// 	return inst;
// }
