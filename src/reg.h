#ifndef REG
#define REG

#include <stdint.h>
#include <stdio.h>
#include "instruction.h"

//REGISTERS
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
        bool valid;

        void clear();
};

class PipeF
{
    public:
        int32_t pc;
        uint32_t valid;

        void clear();
};

class PipeD
{   
    public:
        uint32_t instr;
        uint32_t pc;
        uint32_t cycle;
        uint32_t valid;

        void clear();

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
        uint32_t disp22;
        uint32_t a;
        uint32_t cond;
        Instr instr;
        uint32_t valid;
        CntrlSig sig;

        void clear();
};  

class PipeE
{
    public:
        uint32_t operand1;
        uint32_t operand2;
        uint32_t rd;
        uint32_t disp22;
        uint32_t pc;
        Instr instr;
        uint32_t valid;
        CntrlSig sig;

        void clear();
};

class PipeMA
{
    public:
        uint32_t rd;
        uint32_t ares; //ALU result
        uint32_t pc;
        Instr instr;
        uint32_t valid;
        CntrlSig sig;

        void clear();
};

class PipeX
{
    public:
        uint32_t rd;
        uint32_t pc;
        int32_t data;
        Instr instr;
        uint32_t valid;
        CntrlSig sig;

        void clear();
};

class PipeWB
{
    public:
        int32_t data;
        uint32_t rd;
        Instr instr;
        uint32_t valid;
        CntrlSig sig;

        void clear();
};

class PipeRegister
{
    public:
        PipeRegister();
        PipeF f;
        PipeD d;
        PipeRA a;
        PipeE e;
        PipeMA m;
        PipeX x;
        PipeWB w;
        
        void clear();
        void flush();
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