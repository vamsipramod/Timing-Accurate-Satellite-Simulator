// #include "elf_reader.h"
#include "execute.h"
#include <stdlib.h>

int main(int argc ,char ** argv)
{   
    //IF
    // elf a(argv[1]);
    // a.read_elf_instruction();    
    // a.print_instructions();
    // a.write_instructions();

    
    uint32_t inst = 0x82008003;
    //Decode
    decoded_instr* inst_decoded = (decoded_instr*) malloc (sizeof(decoded_instr));

    decode(inst,inst_decoded);
    set_register(1,10);
    set_register(2,33);
    set_register(3,66);


    //Execute
    print_register_state();
    execute(inst_decoded);
    print_register_state();

    return 0;
}