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
       NANO_LOG(NOTICE,"%s :     WRITE BACK STAGE       \n",__id__.c_str());
       
        if(pr.w.valid)
        {
            NANO_LOG(DEBUG,"%s : Data written : %d [%x]\n",__id__.c_str(),pr.w.data,pr.w.data);
            NANO_LOG(DEBUG,"%s : Written to Register %d\n",__id__.c_str(),pr.w.rd);
            NANO_LOG(DEBUG,"%s : Total no.of cycles Taken for the instruction : %d\n\n",__id__.c_str(),pr.w.instr.cycles);
        }

        else
            NANO_LOG(DEBUG,"%s :  NO JOB, IDLE\n\n",__id__.c_str());
}

Wrt_back::Wrt_back(std::string s)
{
    this->__id__ = s+"W";
}