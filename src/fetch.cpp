#include "fetch.h"


void Fetch::fetch(PipeRegister& pr, std::vector <uint32_t> icache)
{   
    pr.d.instr = icache.at(pr.f.pc);
    pr.d.pc = pr.f.pc;
    pr.d.cycle = 1;
    //pr.pr_fd.instr = icache.at(pc);
    //pr.pr_fd.pc = pc;
}