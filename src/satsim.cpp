#include "satsim.h"


Simulator::Simulator()
{
    // TODO: 
    // Memory ram;
    // Disk hdd;
    initLogger( "mylogfile.log", ldebug);
}

void Simulator::run()
{
    core.pipeline();
}

void Simulator::load(char *input)
{
    elf bin(input);
    bin.read_elf_instruction();
    memory = bin.instructions;
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
    Simulator sim;
    sim.load(argv[1]);      // sim.load(argv[1], addr) -> load the executable to a location in memory
    sim.run();

    return 0;
}