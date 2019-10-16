#include <math.h>

struct decoded_inst{
    uint rd;
    uint rs1;
    
    union{
        uint rs2;
        int simm13;
    } r2;
};

int get_instruction_format(char bit1,char bit2);

uint get_register_number(char reg[],int off);

void decode(char inst[],decoded_inst* d);

int get_simm13(char* reg);