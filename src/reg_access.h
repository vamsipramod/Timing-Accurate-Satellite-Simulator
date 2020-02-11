#ifndef REG_ACCESS
#define REG_ACCESS

#include "reg.h"
#include "NanoLogCpp17.h"

class Reg_access
{   
    private:
    void log(PipeRegister& pr);

    public:
    void reg_access(PipeRegister& pr,Registers reg);
    std::string id;
    void id(std::string s);
    
};

#endif