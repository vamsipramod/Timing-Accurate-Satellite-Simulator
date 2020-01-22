#include "reg.h"


// Registers
void Registers::state()
{   
    printf("================================\n");
    for (int i = 0; i < 32; i++)
    {
        printf("REG %d : %d\n",i,reg_file[i]);
    }
    printf("================================\n");
}

void Registers::init_reg_file()
{
    Registers::pc = 0;
    for(int i=0;i<32;i++)
    {
        Registers::reg_file[i] = 0;
    }
}

void Registers::reg(uint32_t index,int32_t val)
{
    reg_word value = val;
    Registers::reg_file[index] = value;
}

Registers::reg_word Registers::reg(uint32_t index)
{
    return Registers::reg_file[index];
}

PipeRegister::PipeRegister()
{
    f.valid = 0;
    d.valid = 0;
    a.valid = 0;
    e.valid = 0;
    m.valid = 0;
    x.valid = 0;
    w.valid = 0;
}

void PipeF :: clear()
{
    pc  = 0;
    valid = 0;
}

void PipeRA :: clear()
{
    rs1 = 0;
    rs2 = 0;
    rd = 0;
    pc = 0;
    simm13 = 0;
    imm22 = 0;
    disp22 = 0;
    a = 0;
    cond =0; 
    valid = 0;
}

void PipeD::clear()
{
    instr = 0;
    pc = 0;
    cycle = 0;
    valid =0;
}

void PipeE::clear()
{
    operand1 = 0;
    operand2 = 0;
    rd = 0;
    disp22 = 0;
    pc = 0;
    valid = 0;
}

void PipeMA::clear()
{
    rd = 0;
    ares = 0; //ALU result
    pc = 0;
    valid = 0;
}

void PipeX::clear()
{
    rd = 0;
    pc = 0;
    data = 0;
    valid = 0;
}

void PipeWB::clear()
{
    data = 0;
    rd = 0;
    valid = 0;
}

void PipeRegister::clear()
{
    f.clear();
    d.clear();
    a.clear();
    e.clear();
    m.clear();
    x.clear();
    w.clear();   
}

void PipeRegister::flush()
{
    f.clear();
    d.clear();
    a.clear();
    e.clear();
}