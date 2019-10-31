#include "execute.h"

void Execute::execute(Decode::decoded_instr* instr)
{   

    if(instr->opcode1 == 2)
    {
       uint32_t rs1 =  instr->inst_type.a.rs1;
       uint32_t rd =  instr->inst_type.a.rd;

       if(instr->inst_type.a.opcode3 == 0x00000000)
       {
           if(instr->inst_type.a.operand2.intg.i == 0)
           {
               uint32_t rs2 = instr->inst_type.a.operand2.intg.rs2.rs2;
               Registers::get_register(rs1) + Registers::get_register(rs2);
               Registers::set_register(rd, Registers::get_register(rs1) + Registers::get_register(rs2));
           }

           else
           {
               Registers::set_register(rd, Registers::get_register(rs1) + get_simm13(instr->inst_type.a.operand2.intg.rs2.simm13));
           }
           
       }
    
    }

    if(instr->opcode1 == 0)
    {
        uint32_t op = instr->inst_type.b.opcode2;
        if(op == 0x00000004)
        {                           //SETHI
            uint32_t rd = instr->inst_type.b.target.sethi.rd;
            int32_t imm = instr->inst_type.b.target.sethi.imm22;

           
            imm <<= 10;
            Registers::set_register(rd, 0 | imm);  
        }
    }

}

int32_t Execute::get_simm13(int32_t num)
{
    if( (1) & (num >> 12))
        return ((((1<<19)-1)<<12) | num);

    else
        return num;
}
