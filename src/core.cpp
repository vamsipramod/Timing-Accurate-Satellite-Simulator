#include "core.h"

Core::Core()
{
    regs.initialize_registers();
    icache.push_back(0x82008003);
    regs.pc = 0;
}

void Core::pipeline()
{
    //IF
    f.fetch(regs.pregs,regs.pc, icache);
    
    //Decode
    d.decode(regs.pregs);

    //Register Access
    ra.reg_access(regs.pregs,regs);

    // inst* inst_decoded = (inst*) malloc (sizeof(inst));

    //Execute

    // Registers::print_regstate();
    // Execute::execute(inst_decoded);
    // Registers::print_regstate();
}