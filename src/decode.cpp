#include "decode.h"

void decode(uint32_t instr,decoded_instr* d)
{   

    uint32_t instr_copy = instr;

    uint32_t opcode1 = instr_copy >> 30;

    d->opcode1 = opcode1;

    if(opcode1 == 1)
    {
        d->inst_type.c.target_address = (((1 << 22) - 1) & (instr_copy >> (0)));
    }

    else if(opcode1 == 0)
    {
        d->inst_type.b.opcode2 = (((1 << 3) - 1) & (instr_copy >> (22)));

        if(d->inst_type.b.opcode2 == 4)
        {
            d->inst_type.b.target.sethi.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
            d->inst_type.b.target.sethi.imm22 = (((1 << 22) - 1) & (instr_copy >> (0)));
        }

        else
        {
            d->inst_type.b.target.branch.a = (((1) & (instr_copy >> (29))));
            d->inst_type.b.target.branch.cond = (((1 << 4) - 1) & (instr_copy >> (25)));
            d->inst_type.b.target.branch.disp22 = (((1 << 22) - 1) & (instr_copy >> (0)));
        }
    }

    else
    {
        d->inst_type.a.opcode3 = (((1 << 6) - 1) & (instr_copy >> (19)));
        d->inst_type.a.rd = (((1 << 5) - 1) & (instr_copy >> (25)));
        d->inst_type.a.rs1 = (((1 << 5) - 1) & (instr_copy >> (14)));

        if(d->inst_type.a.opcode3 >= 0x00000034 && d->inst_type.a.opcode3 <= 0x00000037)
        {
            d->inst_type.a.operand2.fp.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
            d->inst_type.a.operand2.fp.opf = (((1 << 9) - 1) & (instr_copy >> (5)));
        }

        else
        {
            d->inst_type.a.operand2.intg.i = ((1) & (instr_copy >> (13)));
            if( d->inst_type.a.operand2.intg.i)
            {
                d->inst_type.a.operand2.intg.rs2.simm13 = (((1 << 13) - 1) & (instr_copy >> (0)));
            }
            else
            {
                d->inst_type.a.operand2.intg.rs2.rs2 = (((1 << 5) - 1) & (instr_copy >> (0)));
            }
        }        

    }
        
}