#ifndef EXECUTE
#define EXECUTE

#include "reg.h"

class Execute{

    private:
        void log(PipeRegister& pr,uint32_t pc);
    public:
        void execute(PipeRegister& pr,uint32_t& pc);
};

#endif
