#include "decode.h"

inst Decode::decode_inst(uint32_t instr)
{   
    uint32_t instr_copy = instr;

    inst d;

    uint32_t op = instr_copy >> 30;
    d.op = op;

    switch (op)
    {
        case 1:
            d.inst_type.a.disp30 = (((1 << 22) - 1) & (instr_copy >> (0)));
            break;

        case 0:
            d.inst_type.b.op2 = (((1 << 3) - 1) & (instr_copy >> (22)));

            if(d.inst_type.b.op2 == 4)
            {   
                d.inst_type.b.target.sethi.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
                d.inst_type.b.target.sethi.imm22 = (((1 << 22) - 1) & (instr_copy >> (0)));
            }

            else
            {   
                d.inst_type.b.target.branch.a = (((1) & (instr_copy >> (29))));
                d.inst_type.b.target.branch.cond = (((1 << 4) - 1) & (instr_copy >> (25)));
                d.inst_type.b.target.branch.disp22 = (((1 << 22) - 1) & (instr_copy >> (0)));
            }

            break;
        
        case 2:
        case 3:
            d.inst_type.c.op3 = (((1 << 6) - 1) & (instr_copy >> (19)));
            d.inst_type.c.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
            d.inst_type.c.rs1 = (((1 << 5) - 1) & (instr_copy >> (25)));

            if(d.inst_type.c.op3 >= 0x00000034 && d.inst_type.c.op3 <= 0x00000037)
            {
                d.inst_type.c.operand2.fp.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
                d.inst_type.c.operand2.fp.opf = (((1 << 9) - 1) & (instr_copy >> (5)));
            }

            else
            {
                d.inst_type.c.operand2.intg.i = ((1) & (instr_copy >> (13)));
                if( d.inst_type.c.operand2.intg.i)
                {
                    d.inst_type.c.operand2.intg.rs2.simm13 = (((1 << 13) - 1) & (instr_copy >> (0)));
                }
                else
                {
                    d.inst_type.c.operand2.intg.rs2.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
                }
            }
            break;

        default:
            break;
    }
    return d;       
}

void set_control_regs(inst instr,plregs& r)
{
        
}

void Decode::decode(plregs& r)
{
    inst d = decode_inst(r.pr_fd.instr);
    set_control_regs(d,r);
}