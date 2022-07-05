#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int UnsignedIntImm(unsigned int immediate, int size);

int main()
{
    unsigned int test1 = 0b111111111110; //-2
    unsigned int test2 = 0b111111110110; //-10
    unsigned int test3 = 0b111111110011; //-13
    unsigned int test4 = 0b000000001101; //13
    cout << "TEST: " << UnsignedIntImm(test1,12) << endl;
    cout << "TEST: " << UnsignedIntImm(test2,12) << endl;
    cout << "TEST: " << UnsignedIntImm(test3,12) << endl;
    cout << "TEST: " << UnsignedIntImm(test4,12) << endl;

    system("pause");
    return 0;
}

int UnsignedIntImm(unsigned int immediate, int size)
{
    int finalValue;
    unsigned int firstBit = (immediate >> (size-1)) & 0x1;
    cout << "First bit:"<<firstBit << endl;
    if(firstBit==1)
    {
        unsigned int AllOnes;
        switch (size)
        {
        case(6):
            AllOnes=0x3F;
            break;
        case(7):
            AllOnes = 0x7F;
            break;
        case(12):
            AllOnes = 0xFFF;
            break;
        case(13):
            AllOnes = 0x1FFF;
        case(18):
            AllOnes = 0x3FFFF;
            break;
        case(20):
            AllOnes = 0xFFFFF;
            break;
        default:
            AllOnes = 0xF;
            break;
        }
        unsigned int XORbin = (AllOnes ^ immediate) + 1;
        finalValue = 0 - XORbin;
        return finalValue;
    }
     finalValue= immediate;
    return finalValue;
}





