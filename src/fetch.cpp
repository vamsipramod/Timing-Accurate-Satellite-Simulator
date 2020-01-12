#include "fetch.h"


void Fetch::fetch(PipeRegister& pr, std::vector <uint32_t> icache)
{   
    if(pr.f.valid)
    {   
        pr.d.instr = icache.at(pr.f.pc);
        pr.d.pc = pr.f.pc;
        pr.d.cycle = 1;
        pr.d.valid = 1;
        
        log(pr);
        pr.f.valid = 0;
    }

    else
          log(pr);
}

void Fetch::log(PipeRegister& pr)
{
     printf("------------------------\n");
     printf("    FETCH STAGE        \n");
     printf("------------------------\n");

     if(pr.f.valid)
     {
          printf("Fetching Instruction at address : %x\n", pr.f.pc);
          printf("Instruction at %x :    %x\n\n",pr.f.pc,pr.d.instr);
     }

     else
     {
          printf(" \nNO JOB, IDLE\n\n");
     }
}