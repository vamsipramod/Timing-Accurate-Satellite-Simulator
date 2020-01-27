#ifndef EXECUTE
#define EXECUTE

#include "reg.h"
#include "log.h"

class Execute{

    private:
        void log(PipeRegister& pr,uint32_t pc,bool flush);
    public:
        void execute(PipeRegister& pr,uint32_t& pc,bool& flush);
};

#endif
