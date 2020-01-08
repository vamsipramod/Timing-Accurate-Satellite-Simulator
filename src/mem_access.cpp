#include "mem_access.h"

void Mem_access::mem_access(PipeRegister& pr, std::vector <uint32_t> dcache)
{
    pr.x.pc = pr.m.pc;
    pr.x.rd = pr.m.rd;
    pr.x.instr = pr.m.instr;
    
    if(pr.sig.MemRead == 1)
    {
        pr.x.data = dcache.at(pr.m.ares);
    }
    
    else if(pr.sig.RegWrite == 1)
    {
        pr.x.data = pr.m.ares;
    }
    
}