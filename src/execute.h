#ifndef EXECUTE
#define EXECUTE

#include "reg.h"
#include "NanoLogCpp17.h"

class Execute{

    private:
        void log(PipeRegister& pr,uint32_t pc,bool flush);
    
    public:
        void execute(PipeRegister& pr,uint32_t& pc,bool& flush);
        std::string __id__;
        Execute(std::string s);
};

#endif
