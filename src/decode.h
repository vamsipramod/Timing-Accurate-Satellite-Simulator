#include <stdint.h>

//TODO: 
// Rename each struct here to Format1, Format2, Format3
// Decode to have a union called inst which is union{Format1, Format2, Format3}
// Input to Decode object (instruction-bytes), output -> set the control regs

class Decode {
    
    public :
    typedef struct{
        int32_t target_address;
    } Call;

    typedef struct{
        int32_t opcode3; 
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
    } Arithmetic; //FMT1 or FMT2 or FMT3

    typedef struct{
        uint32_t opcode2;

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
    } Branch;

    typedef struct {
        uint32_t opcode1;
        union 
        {
            Arithmetic a;
            Branch b;
            Call c; 
        } inst_type;
    } decoded_instr;

    static void decode(uint32_t inst,decoded_instr* d);
};


