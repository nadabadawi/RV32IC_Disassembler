# RV32IC_Disassembler

Implementation Details: 
The code makes use of 2 functions, one for each type of instruction word (16 and 32 bits). In each function the instruction word passed is read as different segments, which are used to decode the instruction word. To illustrate, the least significant 7 bits in the 32-bit instruction word are together labelled as "opcode". These segments help in distiguishing the instruction. A switch statement is used to determine the opcode of the instruction, after which a vector of strings is used whenever possible. Each string in the vector is indexed by its "funct3" segment. In some cases, implementing this method is not possible since these instructions do not fit the pattern, for example, the 16-bit instructions.

Contributions: 
Nada Badawi - Implemented S- and I- instruction types (store and immediate types) along with other compressed instructions, such as C.MV, C.LI

Farah Awad - Implemented B- and R- instruction types (branch and register types) along with other compressed instructions, such as C.LWSP, C.SWSP

Nermien Elassy - Implemented J- and U- instruction types (jal and upper types) along with other compressed instructions, such as C.ADDI16SP, C.ADDI4SPN
