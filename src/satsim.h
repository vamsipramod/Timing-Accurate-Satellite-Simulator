#include "core.h"

class Simulator{
    private:
    Core core;
    vector <uint32_t> memory; 

    // TODO: Add other micro-architectural elements
    // Core core;
    // Cache L1;
    // AHB bus;
    // APB p_bus;

    public:
    Simulator();
    void run();
    void load(char* input);
};
