#ifndef MEMORY
#define MEMORY

#include "NanoLogCpp17.h"
#include <stdint.h>
#include <vector>
#include <utility>

typedef uint32_t mem_addr;

class Memory
{   
    private:
    std::vector <uint32_t> text;
    std::vector <uint32_t> data;

    public:

    Memory(std::vector <uint32_t> text,std::vector <uint32_t> data);
    std::pair<uint32_t, bool>  get_instruction(mem_addr addr);
    void set_word(mem_addr addr,uint32_t value);

};

#endif