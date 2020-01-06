#include "core.h"

class Simulator{
    private:
    Core core;
    vector <uint32_t> memory; 

    // TODO: 
    // Logging module
    // Incorporate stalling inside pipeline
    //      - grlib-gpl-1.2.2-b4123/lib/gaisler/leon3v1/iu3.vhd
    //      - Pass-by-value (only indexes) vs Pass-by-reference
    // Refactor code
    // Revisit code for managing Registers
    // Assert statements to see nothing goes wrong accidentally
    // Support loading and storing of entire simulator state.
    //      - Run only a subset of instructions
    //      - Statistics
    // Add other micro-architectural elements
    //      - AHB bus;
    //      - APB p_bus;

    public:
    Simulator();
    void run();
    void load(char* input);
};
