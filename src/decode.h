#include <stdint.h>
#include "reg.h"
//TODO: 
// Rename each struct here to Format1, Format2, Format3
// Decode to have a union called inst which is union{Format1, Format2, Format3}
// Input to Decode object (instruction-bytes), output -> set the control regs


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
        } inst_type;
    } inst;


class Decode {
    
    private:
        inst decode_inst(uint32_t instr);
        void set_control_regs(inst instr,plregs& r);
    public :
        void decode(plregs& r);
};


