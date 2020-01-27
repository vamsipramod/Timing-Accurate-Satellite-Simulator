#include "execute.h"

void Execute::execute(PipeRegister& pr,uint32_t& pc, bool& flush)
{
     LOG(linfo) << "------------------------\n";
     LOG(linfo) << "    EXECUTE STAGE        \n";
     LOG(linfo) << "------------------------\n";
     if(pr.e.valid)
     {
          pr.m.pc = pr.e.pc;
          pr.m.rd = pr.e.rd;
          pr.m.instr = pr.e.instr;
          pr.m.sig = pr.e.sig;
          
          switch (pr.e.sig.ALUop)
          {
               case 0x00000000:    //ADD & LOAD
               {    uint32_t a = pr.e.operand1;
                    uint32_t b = pr.e.operand2;
                    pr.m.ares = a + b;   
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
                    flush = true;
                    pr.e.valid = 1;
                    break;
               }     
               default:
                    break;
          }  
          pr.m.instr.cycles++;
          pr.m.valid = 1;

          log(pr,pc,flush);
          pr.e.valid = 0;
     }

     else
          log(pr,pc,flush);
}

void Execute::log(PipeRegister& pr,uint32_t pc,bool flush)
{
     if(pr.e.valid)
     {    
          switch (pr.e.sig.ALUop)
          {
               case 0x00000000:
                    LOG(ldebug) << "Executing  ADD Instruction\n";
                    LOG(ldebug) << "ALU Output : " << pr.m.ares << "\n\n";
                    break;
               
               case 0x00000004:
                    LOG(ldebug) << "Executing  SETHI Instruction\n";
                    LOG(ldebug) << "ALU Output : " << std::hex << pr.m.ares << "\n\n";
                    break;

               case 0x00000002:
                    LOG(ldebug) << "Executing Branch Always Instruction\n";
                    LOG(ldebug) << "New PC : " << std::hex << pc << "\n\n";   

               default:
                    break;
          }

          if(flush)
          {     LOG(ldebug) << "Branch Taken, PipeLine Flushed Out\n";     }
     }

     else
          LOG(ldebug) << " \nNO JOB, IDLE\n\n";
}

