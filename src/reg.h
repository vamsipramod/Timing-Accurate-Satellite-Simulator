#ifndef REG
#define REG

#include <stdint.h>
#include <stdio.h>

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
        uint32_t ares;
        uint32_t pc;
        Instr instr;
    } pr_em;

    struct 
    {   
        uint32_t rd;
        uint32_t pc;
        uint32_t data;
        Instr instr;
    }pr_mx;
    
    struct 
    {
        uint32_t memout;
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

//INSTRUCTION
typedef struct{
        int32_t disp30;
    } format1;

typedef struct{
        uint32_t op2;

        union 
        {
            struct
            {
                uint32_t rd;
                int32_t imm22;
            } sethi;

            struct 
            {
                int32_t a;
                int32_t cond;
                int32_t disp22;  
            } branch; 
        
        } target;
    } format2;

typedef struct{
        int32_t op3; 
        uint32_t rd;
        uint32_t rs1;

        union 
        {
            struct 
            {
                int i;
                union 
                {
                        uint32_t rs2;
                        int32_t simm13;
                } rs2;
                
            } intg;

            struct 
            {
                uint32_t rs2;
                uint32_t opf;
            } fp;

        } operand2;
    } format3; //FMT1 or FMT2 or FMT3

typedef struct {
        uint32_t op;
        union 
        {
            format1 a;
            format2 b;
            format3 c; 
        } inst;
    } inst_type;

class Instr
{
    private:
        inst_type instr;
    public:
        void disassemble();
};

#endif


