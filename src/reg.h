#include <stdint.h>
#include <stdio.h>


class Registers
{
    public:

        typedef int32_t reg_word;

        static void print_register_state();

        static void initialize_registers();

        static void set_register(uint32_t index,int32_t val);

        static reg_word get_register(uint32_t index);

        static reg_word registers[32];
};





