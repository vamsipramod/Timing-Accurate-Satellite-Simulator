#ifndef ELF_READER
#define ELF_READER

# include <err.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <gelf.h>
#define __STDC_FORMAT_MACROS
#include <vector>

using namespace std;


#define        PRINT_FMT        "    %-20s 0x%jx"

#define        PRINT_FIELD(N) do { \
            (void) printf(PRINT_FMT, #N, (uintmax_t) hdr.N); \
        } while (0)
            //END

#define         NL() do { (void) printf("\n"); }while(0)


class elf
{
    private:
    Elf *e;
    size_t shstrndx;
    unsigned current_instruction_index=0;
    

    public:
    vector <uint32_t> instructions;
    elf(char *input_file);

    void read_elf_instruction();

    uint32_t get_instruciton();

    void print_section_header(Elf_Scn *scn);
    
    void print_instructions();
   
    void write_instructions(char output_file[]);

};

#endif