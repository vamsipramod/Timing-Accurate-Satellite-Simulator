#include "execute.h"

void Execute::execute(PipeRegister& pr,uint32_t& pc)
{
     if(pr.e.valid)
     {
          pr.m.pc = pr.e.pc;
          pr.m.rd = pr.e.rd;
          pr.m.instr = pr.e.instr;
          pr.m.sig = pr.e.sig;
          printf("ALUop : %x\n",pr.e.sig.ALUop);
          switch (pr.e.sig.ALUop)
          {
               case 0x00000000:
               {    uint32_t a = pr.e.operand1;
                    uint32_t b = pr.e.operand2;
                    pr.m.ares = a + b;   //ADD
                    printf("ADD\n");
                    break;
               }
               case 0x00000004:         //SETHI
               {    uint32_t c = pr.e.operand1;
                    pr.m.ares = c << 10;
                    break;
               }
               
               case 0x00000002:         //Branch Always
               {
                    uint32_t new_pc = pr.e.pc + 4*pr.e.disp22;
                    pr.flush();
                    pc = new_pc;
               }     
               default:
                    break;
          }  
          pr.m.instr.cycles++;
          pr.m.valid = 1;

          log(pr,pc);
          pr.e.valid = 0;
     }

     else
          log(pr,pc);
}

void Execute::log(PipeRegister& pr,uint32_t pc)
{
     printf("------------------------\n");
     printf("    EXECUTE STAGE        \n");
     printf("------------------------\n");

     if(pr.e.valid)
     {    
          switch (pr.e.sig.ALUop)
          {
          case 0x00000000:
               printf("Executing  ADD Instruction\n");
               printf("ALU Output : %d\n\n",pr.m.ares);
               break;
          
          case 0x00000004:
               printf("Executing  SETHI Instruction\n");
               printf("ALU Output : %x\n\n",pr.m.ares);
               break;

          case  0x00000002:   
               printf("Executing Branch Always Instruction:");
               printf("New PC : %x\n\n", pc);
          default:
               break;
          }
     }

     else
     {
          printf(" \nNO JOB, IDLE\n\n");
     }
}

