#include "decode.h"
#include <iostream>

struct reg
{
    union 
    {
        int integer;
        char character;
        float decimal;
    } data;
    
};


static reg registers[32];

void execute(decoded_inst* inst_details);
void print_register_state();
void initialize_registers();