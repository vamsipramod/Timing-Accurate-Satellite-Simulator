#include "decode.h"

int32_t simm13(int32_t n)
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
            d.instr.inst_type.a.disp30 = (((1 << 22) - 1) & (instr_copy >> (0)));
            break;

        case 0:
            d.instr.inst_type.b.op2 = (((1 << 3) - 1) & (instr_copy >> (22)));

            if(d.instr.inst_type.b.op2 == 4)
            {   
                d.instr.inst_type.b.target.sethi.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
                d.instr.inst_type.b.target.sethi.imm22 = (((1 << 22) - 1) & (instr_copy >> (0)));
            }

            else
            {   
                d.instr.inst_type.b.target.branch.a = (((1) & (instr_copy >> (29))));
                d.instr.inst_type.b.target.branch.cond = (((1 << 4) - 1) & (instr_copy >> (25)));
                d.instr.inst_type.b.target.branch.disp22 = (((1 << 22) - 1) & (instr_copy >> (0)));
            }

            break;
        
        case 2:
        case 3:
            d.instr.inst_type.c.op3 = (((1 << 6) - 1) & (instr_copy >> (19)));
            d.instr.inst_type.c.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
            d.instr.inst_type.c.rs1 = (((1 << 5) - 1) & (instr_copy >> (14)));

            if(d.instr.inst_type.c.op3 >= 0x00000034 && d.instr.inst_type.c.op3 <= 0x00000037)
            {
                d.instr.inst_type.c.operand2.fp.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
                d.instr.inst_type.c.operand2.fp.opf = (((1 << 9) - 1) & (instr_copy >> (5)));
            }

            else
            {
                d.instr.inst_type.c.operand2.intg.i = ((1) & (instr_copy >> (13)));
                if( d.instr.inst_type.c.operand2.intg.i)
                {
                    d.instr.inst_type.c.operand2.intg.rs2.simm13 = (((1 << 13) - 1) & (instr_copy >> (0)));
                }
                else
                {
                    d.instr.inst_type.c.operand2.intg.rs2.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
                }
            }
            break;

        default:
            break;
    }
    return d;       
}

void Decode::set_control_regs(Instr x,plregs& r)
{
    switch (x.instr.op)
    {
        case 2:
            r.pr_dra.rs1 = x.instr.inst_type.c.rs1;
            r.pr_dra.rd  = x.instr.inst_type.c.rd;
            r.pr_dra.pc  = r.pr_fd.pc;
            r.pr_dra.instr = x;

            if(x.instr.inst_type.c.operand2.intg.i == 0)
                r.pr_dra.rs2 = x.instr.inst_type.c.operand2.intg.rs2.rs2;

            else
                r.pr_dra.simm13 = simm13(x.instr.inst_type.c.operand2.intg.rs2.simm13);

            switch (x.instr.inst_type.c.op3)
            {
                case 0x00000000:                //ADD
                    r.cntrl_sig.ALUop = 0x00000000;
                    r.cntrl_sig.ALUSrc = 1;
                    r.cntrl_sig.Branch = 0;
                    r.cntrl_sig.Jump = 0;
                    r.cntrl_sig.MemRead = 0;
                    r.cntrl_sig.MemtoReg =0;
                    r.cntrl_sig.MemWrite = 0;
                    r.cntrl_sig.RegDst = 1;
                    r.cntrl_sig.RegWrite = 1;
                    break;
                
                default:
                    break;
            }
            break;
    
        default:
            break;
    }    
}

void Decode::decode(plregs& r)
{
    Instr d = decode_inst(r.pr_fd.instr);
    set_control_regs(d,r);
}