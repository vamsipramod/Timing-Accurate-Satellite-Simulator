#include "core.h"

Core::Core()
{
    regs.initialize_registers();
    icache.push_back(0x82008003);
    regs.pc = 0;
}

void Core::pipeline()
{
    //Fetch
    f.fetch(regs.pregs,regs.pc, icache);
    
    //Decode
    d.decode(regs.pregs);

    //Register Access
    ra.reg_access(regs.pregs,regs);

    //Execute
    e.execute(regs.pregs);

    //Memory Access
    m.mem_access(regs.pregs,dcache);

    //Exception
    x.exception(regs.pregs);

    //Write Back
    wb.wrt_back(regs.pregs,regs);
}