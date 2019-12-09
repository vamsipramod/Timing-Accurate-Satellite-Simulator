#include "execute.h"

void Execute::execute(plregs& pr)
{
     int32_t a = pr.pr_rae.operand1;
     int32_t b = pr.pr_rae.operand2;
     pr.pr_em.pc = pr.pr_rae.pc;
     pr.pr_em.rd = pr.pr_rae.rd;
     
     switch (pr.cntrl_sig.ALUop)
     {
          case 0:
               pr.pr_em.ares = a + b;   //ADD
               break;
          
          default:
               break;
     }
     

}

