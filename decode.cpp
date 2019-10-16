#include "decode.h"
#include <iostream>
int get_instruction_format(char bit1,char bit2)
{
    if(bit1 == '1')
        return 2;
    
    else if(bit2 =='1')
        return 1;
    
    else
        return 0;
    
}

uint get_register_number(char reg[],int off)
{   
    uint reg_num=0;
    for(uint i=4+off;i>=off;i--)
    {
        if(reg[i] == '1')
            reg_num += (uint)pow(2,4+off-i);
    }
    return reg_num;
}


int get_simm13(char* reg)
{
    int reg_num=0;
    for(uint i=13;i>=0;i--)
    {
        if(reg[i] == '1')
            reg_num += (int)pow(2,13-i);
    }
    return reg_num;
}

void decode(char inst[],decoded_inst* d)
{   
    int format = get_instruction_format(inst[0],inst[1]);
    
   
    if(format == 2)
    {   
        printf("i am here : d1\n");
        d->rs1 = get_register_number(inst,13);
        printf("i am here : d2\n");
        d->rd = get_register_number(inst,2);
        printf("i am here\n");
        if(inst[18] == '0')
        {
            d->r2.rs2 = get_register_number(inst,27);
        }

        else
        {
            d->r2.simm13 = get_simm13(inst+19);
        }
    }
    
}