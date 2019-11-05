#include "core.h"

Core::Core(char* input)
{
    input_file = input;
}

void Core::pipeline()
{
    //IF
    // char out[] = "instructions.txt";
    elf a(input_file);
    a.read_elf_instruction();    
    // a.print_instructions();
    // a.write_instructions(out);

    uint32_t inst = 0x82008003;

    //Decode
    Decode::decoded_instr* inst_decoded = (Decode::decoded_instr*) malloc (sizeof(Decode::decoded_instr));

    Decode::decode(inst,inst_decoded);
    Registers::set_register(1,10);
    Registers::set_register(2,33);
    Registers::set_register(3,66);


    //Execute
    Registers::print_register_state();
    Execute::execute(inst_decoded);
    Registers::print_register_state();
}