#ifndef EXCEPTION
#define EXCEPTION

#include "reg.h"
#include "log.h"

class Exception
{   
    private:
    void log(PipeRegister& pr);
    public:
    void exception(PipeRegister& pr);
};

#endif