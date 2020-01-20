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
    LOG(linfo) << "------------------------\n";
    LOG(linfo) << "   MEMORY ACCESS STAGE        \n";
    LOG(linfo) << "------------------------\n";

    if(pr.m.valid)
    {
        if(pr.m.sig.MemRead)
        {   
            LOG(ldebug) << "Accessing Memory address " << std::hex << pr.m.ares << "\n";
            LOG(ldebug) << "Data at address location " << pr.x.data << "\n\n";
        }

        else
        {
            LOG(ldebug) << "NO Memory Access is Involved\n\n";
        }
    }
    
    else
        LOG(ldebug) << " \nNO JOB, IDLE\n\n";
}