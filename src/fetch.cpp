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
    NANO_LOG(NOTICE," %s :   FETCH STAGE        \n",__id__.c_str());

     if(pr.f.valid)
     {
          NANO_LOG(DEBUG,"%s : Fetching Instruction at address : %x\n",__id__.c_str(),pr.f.pc);
          NANO_LOG(DEBUG,"%s : Instruction at %x  : %x \n\n",__id__.c_str(),pr.f.pc,pr.d.instr);
     }

     else
         NANO_LOG(DEBUG,"%s : NO JOB, IDLE\n\n",__id__.c_str());
     
}

void Fetch::id(std::string s)
{
    this->__id__ = s+"F";
}