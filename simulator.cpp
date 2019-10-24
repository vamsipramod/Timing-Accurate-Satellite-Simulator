// #include "elf_reader.h"
#include "decode.h"
// #include "execute.h"
#include <stdlib.h>
#include <iostream>


int main(int argc ,char ** argv)
{   
    //IF
    // elf a(argv[1]);
    // a.read_elf_instruction();    
    // a.print_instructions();
    // a.write_instructions();

    //char inst[] = "10000010000000001000000000000011";

    uint32_t inst = 0x82008003;
    //Decode
    decoded_instr* inst_decoded = (decoded_instr*) malloc (sizeof(decoded_instr));
    
    decode(inst,inst_decoded);

    // printf("%8.8x",inst_decoded->opcode1);
    //IE
    // initialize_registers();
    // print_register_state();
    // printf("\n\n");
    // execute(inst_details);
    // print_register_state();


    return 0;
}