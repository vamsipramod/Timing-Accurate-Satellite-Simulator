#include "fetch.h"


void Fetch::fetch(plregs& pr, uint32_t pc,std::vector <uint32_t> icache)
{
    pr.pr_fd.instr = icache.at(pc);
    pr.pr_fd.pc = pc;
}