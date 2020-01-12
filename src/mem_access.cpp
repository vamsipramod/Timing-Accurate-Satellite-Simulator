#include "mem_access.h"

void Mem_access::mem_access(PipeRegister& pr, std::vector <uint32_t> dcache)
{
    if(pr.m.valid)
    {
        pr.x.pc = pr.m.pc;
        pr.x.rd = pr.m.rd;
        pr.x.instr = pr.m.instr;
        
        if(pr.sig.MemRead)
        {
            pr.x.data = dcache.at(pr.m.ares);
        }
        
        else if(pr.sig.RegWrite)
        {
            pr.x.data = pr.m.ares;
        }
        pr.x.instr.cycles++;
        pr.x.valid = 1;

        log(pr);
        pr.m.valid = 0;
    }

    else
        log(pr);
}

void Mem_access::log(PipeRegister& pr)
{
    printf("------------------------\n");
    printf("    MEMORY ACCESS STAGE        \n");
    printf("------------------------\n");

    if(pr.m.valid)
    {
        if(pr.sig.MemRead)
        {
            printf("Accessing Memory address %x:\n",pr.m.ares);
            printf("Data at address location %d:\n\n",pr.x.data);
        }

        else
        {
            printf("NO Memory Access is Involved\n\n");
        }
    }
    
    else
    {
        printf(" \nNO JOB, IDLE\n\n");
    }
}