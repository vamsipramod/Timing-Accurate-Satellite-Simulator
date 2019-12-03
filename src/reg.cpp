#include "reg.h"


// int32_t Registers::registers[32] = {0,0,0,0,0,0};

void Registers::print_regstate()
{   
    printf("================================\n");
    for (int i = 0; i < 32; i++)
    {
        printf("REG %d : %d\n",i,registers[i]);
    }
    printf("================================\n");
}

void Registers::initialize_registers()
{
    Registers::pc = 0;
    for(int i=0;i<32;i++)
    {
        Registers::registers[i] = 0;
    }
}

void Registers::set_register(uint32_t index,int32_t val)
{
    reg_word value = val;
    Registers::registers[index] = value;
}

Registers::reg_word Registers::get_register(uint32_t index)
{
    return Registers::registers[index];
}