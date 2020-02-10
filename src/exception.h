#ifndef EXCEPTION
#define EXCEPTION

#include "reg.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Exception
{   
    private:
    void log(PipeRegister& pr);
    public:
    void exception(PipeRegister& pr);
};

#endif