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
    printf("------------------------\n");
    printf("    EXCEPTION STAGE        \n");
    printf("------------------------\n");

    if(pr.x.valid)
    {
        printf(" NO EXCEPTIONS \n\n");
    }

    else
    {
        printf(" \nNO JOB, IDLE\n\n");
    }
    
}