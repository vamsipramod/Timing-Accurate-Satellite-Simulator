#ifndef FETCH
#define FETCH

#include <stdint.h>
#include <vector>
#include "reg.h"

class Fetch
{   
    private:
    void log(PipeRegister& pr);
    public:
    void fetch(PipeRegister& pr,std::vector <uint32_t> icache);
};

#endif