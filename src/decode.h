#ifndef DECODE
#define DECODE

#include <stdint.h>
#include "reg.h"
//TODO: 
// Input to Decode object (instruction-bytes), output -> set the control regs


int32_t simm13(int32_t n);

class Decode {
    
    private:
        Instr decode_inst(uint32_t instr);
        void set_control_regs(Instr instr,plregs& r);
        
    public :
        void decode(plregs& r);
        
};

#endif