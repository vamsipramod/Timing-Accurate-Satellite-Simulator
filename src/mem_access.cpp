#include "mem_access.h"

void Mem_access::mem_access(plregs& r, vector <uint32_t> dcache)
{
    r.pr_mx.pc = r.pr_em.pc;
    r.pr_mx.rd = r.pr_em.rd;

    if(r.cntrl_sig.MemRead == 1)
    {
        r.pr_mx.data = dcache.at(r.pr_em.ares);
    }
}