#include "reg_access.h"

void Reg_access::reg_access(plregs& pr,Registers regs)
{
    pr.pr_rae.pc = pr.pr_dra.pc;
    pr.pr_rae.operand1 = regs.get_register(pr.pr_dra.rs1);
    pr.pr_rae.operand2 = regs.get_register(pr.pr_dra.rs2);
}