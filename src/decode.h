#ifndef DECODE
#define DECODE

#include <stdint.h>
#include "reg.h"
#include "NanoLogCpp17.h"

//TODO: 
// Input to Decode object (instruction-bytes), output -> set the control regs




class Decode {
    
    private:
        Instr decode_inst(uint32_t instr);
        void set_control_regs(Instr instr,PipeRegister& r);
        int32_t simm13(int32_t n);
        void log(PipeRegister& pr);
        
    public :
        void decode(PipeRegister& pr);
        Decode(std::string id);
        std::string __id__;
        
};

#endif