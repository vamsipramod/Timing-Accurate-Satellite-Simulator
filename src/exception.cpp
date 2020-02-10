#include "exception.h"

void Exception::exception(PipeRegister& pr)
{
    if(pr.x.valid)
    {
        pr.w.instr = pr.x.instr;
        pr.w.data = pr.x.data;
        pr.w.rd = pr.x.rd;
        pr.w.instr.cycles++;
        pr.w.sig = pr.x.sig;
        pr.w.valid = 1;

        log(pr);
        pr.x.valid = 0;
    }
    
    else
        log(pr);
    //Exceptions Need to be Handled here.
}


void Exception::log(PipeRegister& pr)
{
    spdlog::info("    EXCEPTION STAGE       \n");
    // LOG(linfo) << "------------------------\n";
    // LOG(linfo) << "    EXCEPTION STAGE        \n";
    // LOG(linfo) << "------------------------\n";
    
    if(pr.x.valid)
    {
        spdlog::debug(" NO EXCEPTIONS \n\n");
        // LOG(ldebug) << " NO EXCEPTIONS \n\n";
    }

    else
        spdlog::debug(" NO JOB, IDLE\n\n");
        // LOG(ldebug) << " \nNO JOB, IDLE\n\n";
}