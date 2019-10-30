#include "execute.h"


void execute(decoded_instr* instr)
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
               registers[rd] = registers[rs1] + registers[rs2];
           }

           else
           {
               registers[rd] = registers[rs1] + get_simm13(instr->inst_type.a.operand2.intg.rs2.simm13);
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

            registers[rd] = 0;
            imm <<= 10;
            registers[rd] |= imm;  
        }
    }

}

void print_register_state()
{   
    printf("================================\n");
    for (int i = 0; i < 32; i++)
    {
        printf("REG %d : %d\n",i,registers[i]);
    }
    printf("================================\n");
}


void initialize_registers()
{
    for(int i=0;i<32;i++)
    {
        registers[i] = 0;
    }
}

int32_t get_simm13(int32_t num)
{
    if( (1) & (num >> 12))
        return ((((1<<19)-1)<<12) | num);

    else
        return num;
}

void set_register(uint32_t index,int32_t val)
{
    reg_word value = val;
    registers[index] = value;
}

