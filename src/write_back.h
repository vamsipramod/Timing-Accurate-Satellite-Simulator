#ifndef WRT_BACK
#define WRT_BACK

#include "reg.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Wrt_back
{   
    private:
        void log(PipeRegister& pr);
    public:
        void wrt_back(PipeRegister& pr,Registers& regs);
};
#endif