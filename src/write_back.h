#ifndef WRT_BACK
#define WRT_BACK

#include "reg.h"
#include "log.h"

class Wrt_back
{   
    private:
        void log(PipeRegister& pr);
    public:
        void wrt_back(PipeRegister& pr,Registers& regs);
};
#endif