#include "decode.h"

int32_t Decode::simm13(int32_t n)
{
    if((1) & (n >> 12))
        return ((((1<<19)-1)<<12) | n);

    else
        return n;
}

Instr Decode::decode_inst(uint32_t instr)
{   
    uint32_t instr_copy = instr;

    Instr d;

    uint32_t op = instr_copy >> 30;
    d.instr.op = op;

    switch (op)
    {
        case 1:
            d.instr.format.a.disp30 = (((1 << 22) - 1) & (instr_copy >> (0)));
            break;

        case 0:
            d.instr.format.b.op2 = (((1 << 3) - 1) & (instr_copy >> (22)));

            if(d.instr.format.b.op2 == 4)
            {   
                d.instr.format.b.target.sethi.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
                d.instr.format.b.target.sethi.imm22 = (((1 << 22) - 1) & (instr_copy >> (0)));
            }

            else
            {   
                d.instr.format.b.target.branch.a = (((1) & (instr_copy >> (29))));
                d.instr.format.b.target.branch.cond = (((1 << 4) - 1) & (instr_copy >> (25)));
                d.instr.format.b.target.branch.disp22 = (((1 << 22) - 1) & (instr_copy >> (0)));
            }

            break;
        
        case 2:
        case 3:
            d.instr.format.c.op3 = (((1 << 6) - 1) & (instr_copy >> (19)));
            d.instr.format.c.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
            d.instr.format.c.rs1 = (((1 << 5) - 1) & (instr_copy >> (14)));

            if(d.instr.format.c.op3 >= 0x00000034 && d.instr.format.c.op3 <= 0x00000037)
            {
                d.instr.format.c.operand2.fp.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
                d.instr.format.c.operand2.fp.opf = (((1 << 9) - 1) & (instr_copy >> (5)));
            }

            else
            {
                d.instr.format.c.operand2.intg.i = ((1) & (instr_copy >> (13)));
                if( d.instr.format.c.operand2.intg.i)
                {
                    d.instr.format.c.operand2.intg.rs2.simm13 = (((1 << 13) - 1) & (instr_copy >> (0)));
                }
                else
                {
                    d.instr.format.c.operand2.intg.rs2.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
                }
            }
            break;

        default:
            break;
    }
    return d;       
}

void Decode::set_control_regs(Instr x,PipeRegister& pr)
{
    pr.a.instr = x;
    pr.a.pc = pr.d.pc;
    CntrlSig sig;
    switch (x.instr.op)
    {
        case 0:
            switch (x.instr.format.b.op2)
            {
                case 0x00000004:                //SETHI
                    pr.a.rd = x.instr.format.b.target.sethi.rd;
                    pr.a.imm22 = x.instr.format.b.target.sethi.imm22;

                    sig.ALUop = 0x00000004;
                    sig.ALUSrc = false;
                    sig.Branch = false;
                    sig.Jump = false;
                    sig.MemRead = false;
                    sig.MemtoReg =false;
                    sig.MemWrite = false;
                    sig.RegDst = true;
                    sig.RegWrite = true;

                    pr.a.sig = sig;
                    break;
                
                case 0x00000002:                //Branch Always
                    pr.a.cond = x.instr.format.b.target.branch.cond;
                    pr.a.a = x.instr.format.b.target.branch.a;
                    pr.a.disp22 = x.instr.format.b.target.branch.disp22;
                
                    sig.ALUop = 0x00000002;
                    sig.ALUSrc = false;
                    sig.Branch = true;
                    sig.Jump = false;
                    sig.MemRead = false;
                    sig.MemtoReg =false;
                    sig.MemWrite = false;
                    sig.RegDst = false;
                    sig.RegWrite = false;

                    pr.a.sig = sig;
                    break;
                default:
                    break;
            }
            
        case 2:
            pr.a.rs1 = x.instr.format.c.rs1;
            pr.a.rd = x.instr.format.c.rd;
            
            if(x.instr.format.c.operand2.intg.i == 0)
                pr.a.rs2  = x.instr.format.c.operand2.intg.rs2.rs2;

            else
                pr.a.simm13 = simm13(x.instr.format.c.operand2.intg.rs2.simm13);

            switch (x.instr.format.c.op3)
            {
                case 0x00000000:                //ADD
                    sig.ALUop = 0x00000000;
                    sig.ALUSrc = true;
                    sig.Branch = false;
                    sig.Jump = false;
                    sig.MemRead = false;
                    sig.MemtoReg =false;
                    sig.MemWrite = false;
                    sig.RegDst = true;
                    sig.RegWrite = true;

                    pr.a.sig = sig;
                    break;
                
                default:
                    break;
            }
            break;
        
        case 3:
            pr.a.rs1 = x.instr.format.c.rs1;
            pr.a.rd = x.instr.format.c.rd;

            if(x.instr.format.c.operand2.intg.i == 0)
                pr.a.rs2  = x.instr.format.c.operand2.intg.rs2.rs2;

            else
                pr.a.simm13 = simm13(x.instr.format.c.operand2.intg.rs2.simm13);

            switch (x.instr.format.c.op3)
            {
                case 0x00000000:                //LD [Load Word]
                    sig.ALUop = 0x00000000;
                    sig.ALUSrc = true;
                    sig.Branch = false;
                    sig.Jump = false;
                    sig.MemRead = true;
                    sig.MemtoReg =true;
                    sig.MemWrite = false;
                    sig.RegDst = true;
                    sig.RegWrite = true;

                    pr.a.sig = sig;
                    break;
                
                default:
                    break;
            }
            break;
    
        default:
            break;
    }    
}

void Decode::decode(PipeRegister& pr)
{
    if(pr.d.valid)
    {
        Instr d = decode_inst(pr.d.instr);
        set_control_regs(d,pr);
        pr.a.instr.cycles = pr.d.cycle +1;
        pr.a.valid = 1;

        log(pr);
        pr.d.valid = 0;
    }

    else
        log(pr); 
}

void Decode::log(PipeRegister& pr)
{   
    spdlog::info("    DECODE STAGE        \n");

    //  LOG(linfo) << "------------------------\n";
    //  LOG(linfo) << "    DECODE STAGE        \n";
    //  LOG(linfo) << "------------------------\n";

     if(pr.d.valid)
     {       
        spdlog::debug("INSTRUCTION DECODED \n");
        spdlog::debug(" CONTROL SIGNALS ARE SET \n\n");
     }

     else
        spdlog::debug(" NO JOB, IDLE\n\n");
        //  LOG(ldebug) << " \nNO JOB, IDLE\n\n";
}