#include "decode.h"
#include <stdio.h>

typedef int32_t reg_word;

static reg_word registers[32];

void execute(decoded_instr* inst_details);

void print_register_state();

void initialize_registers();

int32_t get_simm13(int32_t num);

void set_register(uint32_t index,int32_t val);