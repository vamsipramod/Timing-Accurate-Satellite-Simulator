#include "elf_reader.h"
#include "execute.h"


class Core{
    private:
    char* input_file;

    public:
    Core(char* input);

    void pipeline();

};