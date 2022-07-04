#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

unsigned int pc = 0x0;

char memory[8 * 1024];

void emitError(string s)
{
    cout << s;
    exit(0);
}
void printArr()
{
    for (int i = 0; i < 8*1024; i++)
    {
        cout << memory[i] << endl;
    }
}
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

        inFile.seekg(0, inFile.beg);
        if (!inFile.read((char*)memory, fsize)) emitError("Cannot read from input file\n");

        while (true) {
            instWord = (unsigned char)memory[pc] |
                (((unsigned char)memory[pc + 1]) << 8);
            
            int two_bits = instWord & 0b11;
            if (two_bits == 3 ) //32_bit_instruction
            {
                 instWord_second_part = (unsigned char)memory[pc+2] |
                    (((unsigned char)memory[pc + 3]) << 8);
                
                    string s1 = to_string(instWord_second_part);
                    string s2 = to_string(instWord);
                    // Concatenating strings
                    string s = s1 + s2;
                    // Converting strings into unsigned int again
                unsigned int IW = stoi(s);
                //InstDec32bit(IW)
                pc += 4;
            }
            else
            {
                //InstDec16bit(instWord)
                pc += 2;
            }
            
            // remove the following line once you have a complete simulator
            if (pc == 20) break;            // stop when PC reached address 32
            //instDecExec(instWord);
            bitset<16> x(instWord);
            cout << x << '\n';
            //cout << hex <<instWord << endl;
        }
        //printArr();
    }
    else emitError("Cannot access input file\n");
}
