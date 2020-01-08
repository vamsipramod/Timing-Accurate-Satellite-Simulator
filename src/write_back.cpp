#include "write_back.h"

void Wrt_back::wrt_back(PipeRegister& pr, Registers& regs)
{
    if(pr.sig.RegWrite)
    {
        uint32_t reg = pr.w.rd;
        int32_t data = pr.w.data;
        regs.reg(reg, data);
    }
}