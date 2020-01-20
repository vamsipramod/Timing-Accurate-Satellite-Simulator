#include "reg_access.h"

void Reg_access::reg_access(PipeRegister& pr,Registers regs)
{   
    if(pr.a.valid)
    {
        pr.e.pc = pr.a.pc;
        pr.e.instr = pr.a.instr;

        if(pr.a.sig.ALUSrc)
        {
            pr.e.operand1 = regs.reg(pr.a.rs1);
            pr.e.operand2 = regs.reg(pr.a.rs2);
            pr.e.rd = pr.a.rd;
        }

        else if(pr.a.sig.ALUop == 0x00000004) //SETHI
        {
            pr.e.operand1 = pr.a.imm22;
            pr.e.rd = pr.a.rd;
        }

        else if(pr.a.sig.ALUop == 0x00000002)
        {
            pr.e.disp22 = pr.a.disp22;
        }
        pr.e.instr.cycles++;
        pr.e.valid = 1;
        pr.e.sig = pr.a.sig;
        log(pr);
        pr.a.valid = 0;
    }

    else
        log(pr);
}

void Reg_access::log(PipeRegister& pr)
{
     LOG(linfo) << "------------------------\n";
     LOG(linfo) << "  REGISTER ACCESS STAGE        \n";
     LOG(linfo) << "------------------------\n";

     if(pr.a.valid)
     {
        if(pr.a.sig.ALUSrc)
        {
            LOG(ldebug) << "ALU Operand1 : " << std::hex << pr.e.operand1 << "\n";
            LOG(ldebug) << "ALU Operand2 : " << std::hex << pr.e.operand2 << "\n\n";
        }
        
        else if(pr.a.sig.ALUop == 0x00000004)
        {   
            LOG(ldebug) << "ALU Operand : " << std::hex << pr.e.operand1 << "\n\n";
        }
    
     }

     else
        LOG(ldebug) << " \nNO JOB, IDLE\n\n";
}