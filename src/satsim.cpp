#include "satsim.h"


Simulator::Simulator(char* input)
{
    input_file = input;

    // Create micro-architectural elements when you create simulator
    // Core core(input_file);
    // TODO: 
    // Memory ram;
    // Disk hdd;
}

void Simulator::run()
{
    Core core(input_file);
    core.pipeline();
}

int main(int argc ,char ** argv)
{
    if (argc !=2) {
        fprintf(stderr, "Unrecognized filename.\n");
        fprintf(stderr, "USAGE:  %s  </path/to/SPARCv8/executable>\n", argv[0]);
        exit(1);
    }

    // TODO: Check for SPARCv8 executable
    //

    // Found SPARCv8 executable. Simulate now
    Simulator sim(argv[1]);
    // sim.load(argv[1], addr) -> load the executable to a location in memory
    sim.run();

    return 0;
}
