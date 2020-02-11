#include "write_back.h"

void Wrt_back::wrt_back(PipeRegister& pr, Registers& regs)
{
    if(pr.w.valid)
    {
        if(pr.w.sig.RegWrite)
        {
            uint32_t reg = pr.w.rd;
            int32_t data = pr.w.data;
            regs.reg(reg, data);
        }
        pr.w.instr.cycles++;

        log(pr);
        pr.w.valid = 0;
    }

    else
        log(pr);
}

void Wrt_back::log(PipeRegister& pr)
{       
       NANO_LOG(NOTICE,"      WRITE BACK STAGE       \n");
       
        if(pr.w.valid)
        {
            NANO_LOG(DEBUG,"\nData written : %d [%x]\n",pr.w.data,pr.w.data);
            NANO_LOG(DEBUG,"Written to Register %d\n",pr.w.rd);
            NANO_LOG(DEBUG,"Total no.of cycles Taken for the instruction : %d\n\n",pr.w.instr.cycles);
        }

        else
            NANO_LOG(DEBUG," NO JOB, IDLE\n\n");
}

void Wrt_back::id(std::string s)
{
    this->__id__ = s+"wb";
}