#include "satsim.h"


Simulator::Simulator()
{
    // TODO: 
    // Memory ram;
    // Disk hdd;
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%l] %v");
    auto file_logger = spdlog::basic_logger_mt("basic_logger", "logfile.log");
    spdlog::set_default_logger(file_logger);
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