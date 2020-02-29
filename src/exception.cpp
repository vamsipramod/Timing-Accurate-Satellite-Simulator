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
    NANO_LOG(NOTICE,"%s :     EXCEPTION STAGE       \n",__id__.c_str());
    
    if(pr.x.valid)
    {
        NANO_LOG(DEBUG,"%s : NO EXCEPTIONS \n\n",__id__.c_str());
    }

    else
        NANO_LOG(DEBUG,"%s :  NO JOB, IDLE\n\n",__id__.c_str());
}

void Exception::id(std::string s)
{
    this->__id__ = s+"X";
}