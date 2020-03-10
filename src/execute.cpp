#include "execute.h"

void Execute::execute(PipeRegister& pr,uint32_t& pc, bool& flush)
{    
     NANO_LOG(NOTICE,"%s :     EXECUTE STAGE        \n",__id__.c_str());

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
                    NANO_LOG(DEBUG,"%s : Executing  ADD Instruction\n",__id__.c_str());
                    NANO_LOG(DEBUG,"%s : ALU Output : %d\n\n",__id__.c_str(),pr.m.ares);
                    break;
               
               case 0x00000004:
                   { NANO_LOG(DEBUG,"%s : Executing  SETHI Instruction\n",__id__.c_str());
                    NANO_LOG(DEBUG,"%s : ALU Output : %d\n\n",__id__.c_str(),pr.m.ares);
                    break;
                   }

               case 0x00000002:
                    NANO_LOG(DEBUG,"%s : Executing Branch Always Instruction\n",__id__.c_str());
                    NANO_LOG(DEBUG,"%s : New PC : %x\n\n",__id__.c_str(),pc);
                    break;

               default:
                    break;
          }

          if(flush)
          {    NANO_LOG(DEBUG,"%s : Branch Taken, PipeLine Flushed Out\n",__id__.c_str()); }

     }

     else
          NANO_LOG(DEBUG,"%s :  NO JOB, IDLE\n\n",__id__.c_str());

}

Execute::Execute(std::string s)
{
    this->__id__ = s+"E";
}

