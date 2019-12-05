#include <stdint.h>
#include <vector>
#include "reg.h"

class Fetch
{
    public:
    void fetch(plregs& pr, uint32_t pc,std::vector <uint32_t> icache);
};