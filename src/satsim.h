#include "core.h"


class Simulator{
    private:
    char* input_file;
    // TODO: Add other micro-architectural elements
    // Core core;
    // Cache L1;
    // AHB bus;
    // APB p_bus;

    public:
    Simulator(char* input);

    void run();
};
