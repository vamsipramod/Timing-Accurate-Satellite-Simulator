#ifndef EXCEPTION
#define EXCEPTION

#include "reg.h"
#include "NanoLogCpp17.h"

class Exception
{   
    private:
    void log(PipeRegister& pr);
    
    public:
    void exception(PipeRegister& pr);
    Exception(std::string id);
    std::string __id__;
};

#endif