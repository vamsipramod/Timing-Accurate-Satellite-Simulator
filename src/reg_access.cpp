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
     printf("------------------------\n");
     printf("  REGISTER ACCESS STAGE        \n");
     printf("------------------------\n");

     if(pr.a.valid)
     {
        if(pr.a.sig.ALUSrc)
        {
            printf("ALU Operand1 : %d\n",pr.e.operand1);
            printf("ALU Operand2 : %d\n\n",pr.e.operand2);
        }
        
        else if(pr.a.sig.ALUop == 0x00000004)
        {
            printf("ALU Operand :%x\n\n",pr.e.operand1);
        }
    
     }

     else
     {
          printf(" \nNO JOB, IDLE\n\n");
     }
}