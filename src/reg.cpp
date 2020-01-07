#include "reg.h"


// Registers
void Registers::state()
{   
    printf("================================\n");
    for (int i = 0; i < 32; i++)
    {
        printf("REG %d : %d\n",i,reg_file[i]);
    }
    printf("================================\n");
}

void Registers::initialize_registers()
{
    Registers::pc = 0;
    for(int i=0;i<32;i++)
    {
        Registers::reg_file[i] = 0;
    }
}

void Registers::reg(uint32_t index,int32_t val)
{
    reg_word value = val;
    Registers::reg_file[index] = value;
}

Registers::reg_word Registers::reg(uint32_t index)
{
    return Registers::reg_file[index];
}