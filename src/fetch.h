#ifndef FETCH
#define FETCH

#include <stdint.h>
#include <vector>
#include "reg.h"

class Fetch
{
    public:
    void fetch(PipeRegister& pr,std::vector <uint32_t> icache);
};

#endif