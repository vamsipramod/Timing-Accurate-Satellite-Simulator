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
    NANO_LOG(NOTICE,"    FETCH STAGE        \n");
    //  spdlog::info("    EXECUTE STAGE        \n");
     // LOG(linfo) << "------------------------\n";
     // LOG(linfo) << "    FETCH STAGE        \n";
     // LOG(linfo) << "------------------------\n";

     if(pr.f.valid)
     {
          NANO_LOG(DEBUG,"Fetching Instruction at address : %x\n",pr.f.pc);
          NANO_LOG(DEBUG,"Instruction at %x  : %x \n\n",pr.f.pc,pr.d.instr);
          //spdlog::debug("Fetching Instruction at address : %x\n",pr.f.pc);
          //spdlog::debug("Instruction at %x  : %x \n\n",pr.f.pc,pr.d.instr);
          // LOG(ldebug) << "Fetching Instruction at address : " << std::hex << pr.f.pc << "\n";
          // LOG(ldebug) << "Instruction at " << std::hex << pr.f.pc << ":\t"<< std::hex << pr.d.instr <<"\n\n";
     }

     else
         NANO_LOG(DEBUG," NO JOB, IDLE\n\n");
     
}

void Fetch::id(std::string s)
{
    this->id = s;
}