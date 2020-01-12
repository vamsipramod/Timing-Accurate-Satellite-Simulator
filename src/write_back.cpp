#include "write_back.h"

void Wrt_back::wrt_back(PipeRegister& pr, Registers& regs)
{
    if(pr.w.valid)
    {
        if(pr.sig.RegWrite)
        {
            uint32_t reg = pr.w.rd;
            int32_t data = pr.w.data;
            regs.reg(reg, data);
        }
        pr.w.instr.cycles++;

        log(pr);
        pr.w.valid = 0;
    }

    else
        log(pr);
}

void Wrt_back::log(PipeRegister& pr)
{
        printf("------------------------\n");
        printf("    WRITE BACK STAGE        \n");
        printf("------------------------\n");

        if(pr.w.valid)
        {
            printf("\nData written : %x \n",pr.w.data);
            printf("Written to Register %d\n\n",pr.w.rd);
            printf("Total no.of cycles Taken for the instruction : %d\n",pr.w.instr.cycles);
        }

        else
        {
            printf(" \nNO JOB, IDLE\n\n");
        }
}