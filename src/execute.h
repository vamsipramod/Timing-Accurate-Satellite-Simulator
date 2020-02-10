#ifndef EXECUTE
#define EXECUTE

#include "reg.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Execute{

    private:
        void log(PipeRegister& pr,uint32_t pc,bool flush);
    public:
        void execute(PipeRegister& pr,uint32_t& pc,bool& flush);
};

#endif
