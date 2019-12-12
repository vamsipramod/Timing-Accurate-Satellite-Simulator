#include "exception.h"

void Exception::exception(plregs& pr)
{
    pr.pr_xwb.instr = pr.pr_mx.instr;
    pr.pr_xwb.memout = pr.pr_mx.data;
    pr.pr_xwb.rd = pr.pr_mx.rd;

    //Exceptions Need to be Handled here.
}


