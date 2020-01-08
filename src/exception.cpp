#include "exception.h"

void Exception::exception(PipeRegister& pr)
{
    pr.w.instr = pr.x.instr;
    pr.w.data = pr.x.data;
    pr.w.rd = pr.x.rd;

    //Exceptions Need to be Handled here.
}


