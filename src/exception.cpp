#include "exception.h"

void Exception::exception(PipeRegister& pr)
{
    if(pr.e.valid)
    {
        pr.w.instr = pr.x.instr;
        pr.w.data = pr.x.data;
        pr.w.rd = pr.x.rd;
        pr.w.instr.cycles++;
        pr.w.valid = true;
        pr.e.valid = false;
    }
    
    //Exceptions Need to be Handled here.
}


