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
    NANO_LOG(NOTICE,"%s :    MEMORY ACCESS STAGE         \n",__id__.c_str());

    if(pr.m.valid)
    {
        if(pr.m.sig.MemRead)
        {   
            NANO_LOG(DEBUG,"%s : Accessing Memory address %x\n",__id__.c_str(),pr.m.ares);
            NANO_LOG(DEBUG,"%s : Data at address location %d\n\n",__id__.c_str(),pr.x.data);
        }

        else
        {
            NANO_LOG(DEBUG,"%s : NO Memory Access is Involved\n\n",__id__.c_str());
        }
    }
    
    else
        NANO_LOG(DEBUG,"%s :  NO JOB, IDLE\n\n",__id__.c_str());
}

void Mem_access::id(std::string s)
{
    this->__id__ = s+"M";
}