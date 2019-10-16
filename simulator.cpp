// #include "elf_reader.h"
// #include "decode.h"
#include "execute.h"

int main(int argc ,char ** argv)
{   
    //IF
    // elf a(argv[1]);
    // a.read_elf_instruction();    
    // a.print_instructions();
    // a.write_instructions();

    char inst[] = "10000010000000001000000000000011";


    //Decode
    decoded_inst* inst_details = (decoded_inst*)malloc(sizeof(decoded_inst));
    
    decode(inst,inst_details);

   
    //IE
    initialize_registers();
    print_register_state();
    printf("\n\n");
    execute(inst_details);
    print_register_state();


    return 0;
}