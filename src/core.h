#ifndef CORE
#define CORE

#include "elf_reader.h"
#include "fetch.h"
#include "decode.h"
#include "reg_access.h"
#include "execute.h"
#include "mem_access.h"
#include "exception.h"
#include "write_back.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

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

    private:
    PipeRegister pr;
    Registers regs;
    Fetch f;
    Decode d;
    Reg_access ra;
    Execute e;
    Mem_access m;
    Exception x;
    Wrt_back wb;

    public:
    Core();
    vector <uint32_t> icache;
    vector <uint32_t> dcache; 
    void pipeline();

};

void print_pregs(PipeRegister pr,char s);
#endif