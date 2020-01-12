#ifndef MEM_ACCESS
#define MEM_ACCESS

#include "reg.h"
#include <vector>


class Mem_access
{   
    private:
    void log(PipeRegister& pr);
    public:
    void mem_access(PipeRegister& pr, std::vector <uint32_t> dcache);
};
#endif