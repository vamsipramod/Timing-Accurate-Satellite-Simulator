#include "elf_reader.h"
#include "execute.h"
#include "fetch.h"
#include "reg_access.h"
class Core{

    // TODO: micro-architectural elements
    // Fetch f;
    // Decode d;
    //
    // Register files, condition codes, PC, nPC, trap
    // Pipeline Registers -> pr_fd, pr_da, pr_ae, pr_em, pr_mx;
    //
    // Internal structures -> pointing to which register to read/write (to
    // match with that in VHDL for cycle-accuracy)

    public:
    Core();
    vector <uint32_t> icache; 
    Registers regs;
    Decode d;
    Fetch f;
    Reg_access ra;

    void pipeline();

};
