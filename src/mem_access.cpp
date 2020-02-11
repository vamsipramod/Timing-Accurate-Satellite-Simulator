#include "mem_access.h"

void Mem_access::mem_access(PipeRegister& pr, std::vector <uint32_t> dcache)
{
    if(pr.m.valid)
    {
        pr.x.pc = pr.m.pc;
        pr.x.rd = pr.m.rd;
        pr.x.instr = pr.m.instr;
        pr.x.sig = pr.m.sig;

        if(pr.m.sig.MemRead)
        {
            pr.x.data = dcache.at(pr.m.ares);
        }
        
        else if(pr.m.sig.RegWrite)
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
    NANO_LOG(NOTICE,"   MEMORY ACCESS STAGE         \n");

    if(pr.m.valid)
    {
        if(pr.m.sig.MemRead)
        {   
            NANO_LOG(DEBUG,"Accessing Memory address %x\n",pr.m.ares);
            NANO_LOG(DEBUG,"Data at address location %d\n\n",pr.x.data);
        }

        else
        {
            NANO_LOG(DEBUG,"NO Memory Access is Involved\n\n");
        }
    }
    
    else
        NANO_LOG(DEBUG," NO JOB, IDLE\n\n");
}

void Mem_access::id(std::string s)
{
    this->__id__ = s+"M";
}