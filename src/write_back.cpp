#include "write_back.h"

void Wrt_back::wrt_back(plregs& pr, Registers& regs)
{
    if(pr.cntrl_sig.RegWrite)
    {
        uint32_t reg = pr.pr_xwb.rd;
        int32_t data = pr.pr_xwb.data;
        regs.set_register(reg, data);
    }
}