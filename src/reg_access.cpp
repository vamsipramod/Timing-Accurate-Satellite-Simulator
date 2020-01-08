#include "reg_access.h"

void Reg_access::reg_access(plregs& pr,Registers regs)
{
    pr.pr_rae.pc = pr.pr_dra.pc;
    pr.pr_rae.operand1 = regs.reg(pr.pr_dra.rs1);
    pr.pr_rae.operand2 = regs.reg(pr.pr_dra.rs2);
    pr.pr_rae.rd = pr.pr_dra.rd;
    pr.pr_rae.instr = pr.pr_dra.instr;
}