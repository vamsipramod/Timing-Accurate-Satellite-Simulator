#include <stdint.h>
#include <stdio.h>

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
    } pr_dra;

    struct 
    {
        uint32_t operand1;
        uint32_t operand2;
        uint32_t pc;
    } pr_rae;
    
    struct 
    {
        uint32_t rd;
        uint32_t aout;

    } pr_em;

    struct 
    {
        uint32_t memout;
        uint32_t rd;
    } pr_mwb;

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

class Registers
{
    public:
        uint32_t pc;
        typedef int32_t reg_word;
        void print_regstate();
        void initialize_registers();
        void set_register(uint32_t index,int32_t val);
        reg_word get_register(uint32_t index);
        reg_word registers[32];
        plregs pregs;
};





