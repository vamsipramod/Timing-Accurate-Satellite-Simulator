#ifndef INSTRUCTION
#define INSTRUCTION

#include <stdint.h>
#include <stdio.h>

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
        } format;
    } inst;

class Instr
{
    public:
        inst instr;
        void disassemble();
};

#endif