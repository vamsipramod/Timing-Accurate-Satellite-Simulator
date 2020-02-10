#include "reg_access.h"

void Reg_access::reg_access(PipeRegister& pr,Registers regs)
{   
    if(pr.a.valid)
    {
        pr.e.pc = pr.a.pc;
        pr.e.instr = pr.a.instr;
        
        switch (pr.a.sig.ALUop)
        {
            case 0x00000000:    //ADD & LOAD
                if(pr.a.instr.instr.format.c.operand2.intg.i)
                {
                    pr.e.operand1 = regs.reg(pr.a.rs1);
                    pr.e.operand2 = regs.reg(pr.a.rs2);
                    pr.e.rd = pr.a.rd;
                }

                else
                {
                    pr.e.operand1 = regs.reg(pr.a.rs1);
                    pr.e.operand2 = pr.a.simm13;
                    pr.e.rd = pr.a.rd;
                }
                
                break;

            case 0x00000004:    //SETHI
                {
                    pr.e.operand1 = pr.a.imm22;
                    pr.e.rd = pr.a.rd;
                }
                break;
            
            case 0x00000002:     //Branch Always
                {
                    pr.e.disp22 = pr.a.disp22;
                }
                break;
            
            default:
                break;
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
    spdlog::info("   MEMORY ACCESS STAGE         \n");
    //  LOG(linfo) << "------------------------\n";
    //  LOG(linfo) << "  REGISTER ACCESS STAGE        \n";
    //  LOG(linfo) << "------------------------\n";

     if(pr.a.valid)
     {
        if(pr.a.sig.ALUSrc)
        {
            spdlog::debug("ALU Operand1 : %x\n",pr.e.operand1);
            spdlog::debug("ALU Operand2 : %x\n\n",pr.e.operand2);
            //LOG(ldebug) << "ALU Operand1 : " << std::hex << pr.e.operand1 << "\n";
            //LOG(ldebug) << "ALU Operand2 : " << std::hex << pr.e.operand2 << "\n\n";
        }
        
        else if(pr.a.sig.ALUop == 0x00000004)
        {   
            spdlog::debug("ALU Operand : %x\n\n",pr.e.operand1);
            // LOG(ldebug) << "ALU Operand : " << std::hex << pr.e.operand1 << "\n\n";
        }
     }

     else
        spdlog::debug(" NO JOB, IDLE\n\n");
}