#ifndef FETCH
#define FETCH

#include <stdint.h>
#include <vector>
#include "reg.h"
#include "NanoLogCpp17.h"
#include "instruction.h"
class Fetch
{   
    private:
    void log(PipeRegister& pr);

    public:
    Fetch(std::string id);
    void fetch(PipeRegister& pr,std::vector <uint32_t> icache);
    std::string __id__;

};

#endif