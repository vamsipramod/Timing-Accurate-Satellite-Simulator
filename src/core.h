#include "elf_reader.h"
#include "execute.h"


class Core{
    private:
    char* input_file;
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
    Core(char* input);

    void pipeline();

};
