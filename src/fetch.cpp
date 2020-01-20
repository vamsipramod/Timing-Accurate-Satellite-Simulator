#include "fetch.h"


void Fetch::fetch(PipeRegister& pr, std::vector <uint32_t> icache)
{   
    if(pr.f.valid)
    {   
        pr.d.instr = icache.at(pr.f.pc);
        pr.d.pc = pr.f.pc;
        pr.d.cycle = 1;
        pr.d.valid = 1;
        
        log(pr);
        pr.f.valid = 0;
    }

    else
          log(pr);
}

void Fetch::log(PipeRegister& pr)
{
     LOG(linfo) << "------------------------\n";
     LOG(linfo) << "    FETCH STAGE        \n";
     LOG(linfo) << "------------------------\n";

     if(pr.f.valid)
     {
          LOG(ldebug) << "Fetching Instruction at address : " << std::hex << pr.f.pc << "\n";
          LOG(ldebug) << "Instruction at " << std::hex << pr.f.pc << ":\t"<< std::hex << pr.d.instr <<"\n\n";
     }

     else
          LOG(ldebug) << " \nNO JOB, IDLE\n\n";
     
}