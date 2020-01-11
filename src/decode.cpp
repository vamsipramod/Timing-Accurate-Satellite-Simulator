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
    switch (x.instr.op)
    {
        case 0:
            switch (x.instr.format.b.op2)
            {
                case 0x00000004:                //SETHI
                    pr.a.rd = x.instr.format.b.target.sethi.rd;
                    pr.a.imm22 = x.instr.format.b.target.sethi.imm22;
                    pr.sig.ALUop = 0x00000004;
                    pr.sig.ALUSrc = 0;
                    pr.sig.Branch = 0;
                    pr.sig.Jump = 0;
                    pr.sig.MemRead = 0;
                    pr.sig.MemtoReg =0;
                    pr.sig.MemWrite = 0;
                    pr.sig.RegDst = 1;
                    pr.sig.RegWrite = 1;
                    break;
                
                case 0x00000002:                //Branch Always
                    pr.a.cond = x.instr.format.b.target.branch.cond;
                    pr.a.a = x.instr.format.b.target.branch.a;
                    pr.a.disp22 = x.instr.format.b.target.branch.disp22;
                
                    pr.sig.ALUop = 0x00000002;
                    pr.sig.ALUSrc = 0;
                    pr.sig.Branch = 1;
                    pr.sig.Jump = 0;
                    pr.sig.MemRead = 0;
                    pr.sig.MemtoReg =0;
                    pr.sig.MemWrite = 0;
                    pr.sig.RegDst = 0;
                    pr.sig.RegWrite = 0;
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
                    pr.sig.ALUop = 0x00000000;
                    pr.sig.ALUSrc = 1;
                    pr.sig.Branch = 0;
                    pr.sig.Jump = 0;
                    pr.sig.MemRead = 0;
                    pr.sig.MemtoReg =0;
                    pr.sig.MemWrite = 0;
                    pr.sig.RegDst = 1;
                    pr.sig.RegWrite = 1;
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
        d.cycles = pr.d.cycle;
        set_control_regs(d,pr);
        pr.a.instr.cycles++;
        pr.a.valid = true;
        pr.d.valid = false;
    } 
}