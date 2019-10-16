#include "execute.h"


void execute(decoded_inst* inst_details)
{
    uint r1 = inst_details->rs1;
    uint r2 = inst_details->r2.rs2;
    uint rd = inst_details->rd;

    registers[rd].data.integer = registers[r1].data.integer + registers[r2].data.integer;
}


void print_register_state()
{
    for (int i = 0; i < 32; i++)
    {
        printf("REG %d : %d\n",i,registers[i].data.integer);
    }
}


void initialize_registers()
{
    for(int i=0;i<32;i++)
    {
        registers[i].data.integer = 1;
    }
}

