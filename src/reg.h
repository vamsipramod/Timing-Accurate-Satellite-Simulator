#ifndef REG
#define REG

#include <stdint.h>
#include <stdio.h>
#include "instruction.h"

//REGISTERS
typedef struct
{
    struct
    {
        uint32_t instr;
        uint32_t pc;
    } pr_fd;

    struct
    {
        uint32_t rs1;
        uint32_t rs2;
        uint32_t rd;
        uint32_t pc;
        int32_t simm13;
        Instr instr;
    } pr_dra;

    struct
    {
        uint32_t operand1;
        uint32_t operand2;
        uint32_t rd;
        uint32_t pc;
        Instr instr;
    } pr_rae;

    struct
    {
        uint32_t rd;
        uint32_t ares; //ALU result
        uint32_t pc;
        Instr instr;
    } pr_em;

    struct
    {
        uint32_t rd;
        uint32_t pc;
        int32_t data;
        Instr instr;
    } pr_mx;

    struct
    {
        int32_t data;
        uint32_t rd;
        Instr instr;
    } pr_xwb;

    struct
    {
        int32_t RegDst;
        int32_t ALUSrc;
        int32_t MemtoReg;
        int32_t RegWrite;
        int32_t MemRead;
        int32_t MemWrite;
        int32_t Branch;
        int32_t Jump;
        int32_t ALUop;
    } cntrl_sig;

} plregs;

class PipeF
{
    public:
        int32_t pc;
};

class PipeD
{   
    public:
        uint32_t instr;
        uint32_t pc;
};

class PipeRA
{
    public:
        uint32_t rs1;
        uint32_t rs2;
        uint32_t rd;
        uint32_t pc;
        int32_t simm13;
        uint32_t imm22;
        Instr instr;
};  

class PipeE
{
    public:
        uint32_t operand1;
        uint32_t operand2;
        uint32_t rd;
        uint32_t pc;
        Instr instr;
};

class PipeMA
{
    public:
        uint32_t rd;
        uint32_t ares; //ALU result
        uint32_t pc;
        Instr instr;
};

class PipeX
{
    public:
        uint32_t rd;
        uint32_t pc;
        int32_t data;
        Instr instr;
};

class PipeWB
{
    public:
        int32_t data;
        uint32_t rd;
        Instr instr;
};

class CntrlSig
{
    public:
        bool RegDst;
        bool ALUSrc;
        bool MemtoReg;
        bool RegWrite;
        bool MemRead;
        bool MemWrite;
        bool Branch;
        bool Jump;
        uint32_t ALUop;
};

class PipeRegister
{
    public:
        PipeF f;
        PipeD d;
        PipeRA a;
        PipeE e;
        PipeMA m;
        PipeX x;
        PipeWB w;
        CntrlSig sig;
};

class Registers
{
private:
    typedef int32_t reg_word;
    reg_word reg_file[32]; 

public:
    uint32_t pc; 
    void state();
    void init_reg_file();
    void reg(uint32_t index, int32_t val); // TODO: register(uint32_t index,int32_t val)
    reg_word reg(uint32_t index);          // TODO: register(uint32_t index)
                                           // TODO: Change 32 to a config knob, rename 'registers' to 'register_file' or 'rf' or 'reg_file'
    plregs pregs;
}; // TODO: Do not mix the control registers and data registers into the same class.

// Register -> Abstract class -> register(index), and register(index, value)
// PipeRegister -> Derives from Register  (No configurations)
//    - Stage registers could be subclasses.
//    - code will be pr.f, pr.d, pr.a, pr.e, pr.m, pr.w, pr.x.
//    - Think of using enums to map names to indexes
// RegisterFile -> Derives from Register  (Can be configured by the user)
//    - Register windows? CWP and WIM
//

#endif