#ifndef MEM_ACCESS
#define MEM_ACCESS

#include "reg.h"
#include <vector>


class Mem_access
{
    public:
    void mem_access(PipeRegister& pr, std::vector <uint32_t> dcache);
};
#endif