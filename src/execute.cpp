#include "execute.h"

void Execute::execute(Decode::decoded_instr* instr)
{

    if(instr->opcode1 == 2)
    {
       int32_t rs1 =  Registers::get_register(instr->inst_type.a.rs1);
       uint32_t rd =  instr->inst_type.a.rd;
       int32_t rs2 = 0;

       if(instr->inst_type.a.operand2.intg.i == 0)
       {
            rs2 = Registers::get_register(instr->inst_type.a.operand2.intg.rs2.rs2);
       }
       else
       {
            rs2 = get_simm13(instr->inst_type.a.operand2.intg.rs2.simm13);
       }

       if(instr->inst_type.a.opcode3 == 0x00000000)
       {                                                    //ADD
            Registers::set_register(rd,rs1+rs2);
       }

       else if(instr->inst_type.a.opcode3 == 0x00000001)   //AND
       {
            Registers::set_register(rd,(rs1 & rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000011)   //ANDcc
       {
            Registers::set_register(rd,(rs1 & rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000005)   //ANDN
       {
            Registers::set_register(rd,(rs1 & ~rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000015)   //ANDNcc
       {
            Registers::set_register(rd,(rs1 & ~rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000002)   //OR
       {
            Registers::set_register(rd,(rs1 | rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000012)   //ORcc
       {
            Registers::set_register(rd,(rs1 | rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000006)   //ORN
       {
            Registers::set_register(rd,(rs1 | ~rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000016)   //ORNcc
       {
            Registers::set_register(rd,(rs1 | ~rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000003)   //XOR
       {
            Registers::set_register(rd,(rs1 ^ rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000013)   //XORcc
       {
            Registers::set_register(rd,(rs1 ^ rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000007)   //XNOR
       {
            Registers::set_register(rd,~(rs1 ^ rs2));
       }

       else if(instr->inst_type.a.opcode3 == 0x00000017)   //XNORcc
       {
            Registers::set_register(rd,~(rs1 ^ rs2));
       }
    
    }

    if(instr->opcode1 == 0)
    {
        uint32_t op2 = instr->inst_type.b.opcode2;
        if(op2 == 0x00000004)
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
