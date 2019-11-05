#include "simulator.h"


Simulator::Simulator(char* input)
{
    input_file = input;
}

void Simulator::run_simulator()
{
    Core core(input_file);
    core.pipeline();
}


int main(int argc ,char ** argv)
{
    Simulator sim(argv[1]);
    sim.run_simulator();

    return 0;
}