#include "core.h"

Core::Core()
{   
    regs.init_reg_file();
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x09200000);  //SETHI
    icache.push_back(0x10800001);  //Branch Always
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x82008003); //ADD
    
    regs.pc = 0;
    regs.reg(1,10);
    regs.reg(2,20);
    regs.reg(3,30);
    regs.reg(4,40);
    regs.reg(5,50);
}

void Core::id(string i)
{
    this->id = "cpu" + i;
}

void Core:: pipeline()
{
    bool run = true;
    bool flush = false;
    uint32_t cyc = 1;
    
    // LOG(ldebug) << "Pipeline Started\n";
    // spdlog::info("Pipeline Started\n");
    NANO_LOG(NOTICE,"Pipeline Started\n");

    while(run)
    { 
        // LOG(ldebug) << "=========================CYCLE"<<cyc++<<"============================\n";
        // spdlog::debug("=========================CYCLE %d ============================\n",cyc++); 
        NANO_LOG(DEBUG,"=========================CYCLE %d ============================\n",cyc++);    
        
        //Write Back
        wb.wrt_back(pr,regs);

        //Exception
        x.exception(pr);

        //Memory Access
        m.mem_access(pr,dcache);

        //Execute
        e.execute(pr,regs.pc,flush);

        if(flush)
            { flush = false; continue; }

        //Register Access
        ra.reg_access(pr,regs);
       
        //Decode
        d.decode(pr);

        
        if(regs.pc >= icache.size())
            pr.f.valid = 0;
        else
            pr.f.valid = 1;

        pr.f.pc = regs.pc;
        //Fetch
        f.fetch(pr, icache);

        regs.pc++;
        run = pr.f.valid | pr.d.valid | pr.a.valid | pr.e.valid | pr.m.valid | pr.x.valid | pr.w.valid;
    }
    
}