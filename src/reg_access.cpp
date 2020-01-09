#include "reg_access.h"

void Reg_access::reg_access(PipeRegister& pr,Registers regs)
{   
    pr.e.pc = pr.a.pc;
    pr.e.instr = pr.a.instr;

    if(pr.sig.ALUSrc)
    {
        pr.e.operand1 = regs.reg(pr.a.rs1);
        pr.e.operand2 = regs.reg(pr.a.rs2);
        pr.e.rd = pr.a.rd;
    }

    else if(pr.sig.ALUop == 0x00000004) //SETHI
    {
        pr.e.operand1 = pr.a.imm22;
        pr.e.rd = pr.a.rd;
    }
}