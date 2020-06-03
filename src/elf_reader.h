#ifndef ELF_READER
#define ELF_READER

# include <err.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <gelf.h>
# include <string.h>

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
    

    public:

    elf(char *input_file);
    vector<uint32_t> read_section(char* section);
    void print_section_header(Elf_Scn *scn);
    void write_text_section(char output_file[]);

};

#endif