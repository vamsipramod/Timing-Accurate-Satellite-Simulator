#ifndef FETCH
#define FETCH

#include <stdint.h>
#include <vector>
#include "reg.h"
#include "NanoLogCpp17.h"

class Fetch
{   
    private:
    void log(PipeRegister& pr);

    public:
    void fetch(PipeRegister& pr,std::vector <uint32_t> icache);
    std::string __id__;
    void id(std::string id);

};

#endif