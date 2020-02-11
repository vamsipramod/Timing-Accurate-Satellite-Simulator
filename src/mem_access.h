#ifndef MEM_ACCESS
#define MEM_ACCESS

#include "NanoLogCpp17.h"
#include "reg.h"
#include <vector>

class Mem_access
{   
    private:
    void log(PipeRegister& pr);

    public:
    void mem_access(PipeRegister& pr, std::vector <uint32_t> dcache);
    std::string id;
    void id(std::string s);
};
#endif