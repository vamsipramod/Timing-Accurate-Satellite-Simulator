#include "execute.h"

void Execute::execute(PipeRegister& pr)
{
     uint32_t a = pr.e.operand1;
     uint32_t b = pr.e.operand2;
     pr.m.pc = pr.e.pc;
     pr.m.rd = pr.e.rd;
     pr.m.instr = pr.e.instr;

     switch (pr.sig.ALUop)
     {
          case 0:
               pr.m.ares = a + b;   //ADD
               break;
          
          default:
               break;
     }
     

}

