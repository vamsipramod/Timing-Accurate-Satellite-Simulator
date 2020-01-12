#ifndef REG_ACCESS
#define REG_ACCESS

#include "reg.h"

class Reg_access
{   
    private:
    void log(PipeRegister& pr);
    public:
    void reg_access(PipeRegister& pr,Registers reg);
    
};

#endif