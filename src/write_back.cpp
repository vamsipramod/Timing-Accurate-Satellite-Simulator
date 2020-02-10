#include "write_back.h"

void Wrt_back::wrt_back(PipeRegister& pr, Registers& regs)
{
    if(pr.w.valid)
    {
        if(pr.w.sig.RegWrite)
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
        spdlog::info("   WRITE BACK STAGE         \n");
        // LOG(linfo) << "------------------------\n";
        // LOG(linfo) << "    WRITE BACK STAGE        \n";
        // LOG(linfo) << "------------------------\n";

        if(pr.w.valid)
        {
            spdlog::debug("\nData written : %d [%x]\n",pr.w.data,pr.w.data);
            spdlog::debug("Written to Register %d\n",pr.w.rd);
            spdlog::debug("Total no.of cycles Taken for the instruction : %d\n\n",pr.w.instr.cycles);
            // LOG(ldebug) << "\nData written : " << pr.w.data << " ("<<std::hex<<pr.w.data<<")\n";
            // LOG(ldebug) << "Written to Register " << pr.w.rd << "\n\n";
            // LOG(ldebug) << "Total no.of cycles Taken for the instruction : " << pr.w.instr.cycles << "\n\n";
        }

        else
           spdlog::debug(" \nNO JOB, IDLE\n\n");
}