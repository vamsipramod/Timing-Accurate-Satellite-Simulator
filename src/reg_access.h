#ifndef REG_ACCESS
#define REG_ACCESS

#include "reg.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Reg_access
{   
    private:
    void log(PipeRegister& pr);
    public:
    void reg_access(PipeRegister& pr,Registers reg);
    
};

#endif