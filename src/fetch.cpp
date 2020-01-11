#include "fetch.h"


void Fetch::fetch(PipeRegister& pr, std::vector <uint32_t> icache)
{   
    if(pr.f.valid)
    {   
        pr.d.instr = icache.at(pr.f.pc);
        pr.d.pc = pr.f.pc;
        pr.d.cycle = 1;
        pr.d.valid = true;
        pr.f.valid = false;
    }
}