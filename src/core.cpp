#include "core.h"

Core::Core()
{
    regs.init_reg_file();
    icache.push_back(0x82008003);
    regs.pc = 0;
    regs.reg(1,10);
    regs.reg(2,20);
    regs.reg(3,30);
    regs.reg(4,40);
    regs.reg(5,50);
}

void Core:: pipeline()
{
    printf("Pipeline Started \n");
    printf("Executing Instruction at PC: %x [ADD R1,R2,R3]\n",regs.pc);

    //Fetch
    f.fetch(pr, icache);
    print_pregs(regs.pregs,'F');
    
    //Decode
    d.decode(pr);
    print_pregs(regs.pregs,'D');

    //Register Access
    ra.reg_access(pr,regs);
    print_pregs(regs.pregs,'R');

    //Execute
    e.execute(pr);
    print_pregs(regs.pregs,'E');

    //Memory Access
    m.mem_access(pr,dcache);
    print_pregs(regs.pregs,'M');

    //Exception
    x.exception(pr);
    print_pregs(regs.pregs,'X');

    //Write Back
    wb.wrt_back(pr,regs);
    print_pregs(regs.pregs,'W');
}

void print_pregs(plregs pr,char s)
{
    switch (s)
    {
        case 'F':
            printf("===================================\n");
            printf("FETCH STAGE COMPLETED\n");
            printf("Instruction : %x\n",pr.pr_fd.instr);
            printf("PC : %d\n",pr.pr_fd.pc);
            break;

        case 'D':
            printf("===================================\n");
            printf("DECODE STAGE COMPLETED\n");
            printf(" Source Register A  : %d\n",pr.pr_dra.rs1);
            printf(" Source Register B  : %d\n",pr.pr_dra.rs2);
            printf(" Destination Register : %d\n",pr.pr_dra.rd);
            break;
        
        case 'R':
            printf("===================================\n");
            printf("REGISTER ACCESS COMPLETED\n");
            printf(" Operand 1 : %d\n",pr.pr_rae.operand1);
            printf(" Operand 2 : %d\n",pr.pr_rae.operand2);
            break;
        
        case 'E':
            printf("===================================\n");
            printf("EXECUTE STAGE COMPLETED\n");
            printf("ALU output : %d\n",pr.pr_em.ares);
            break;
        
        case 'M':
            printf("===================================\n");
            printf("MEMORY ACCESS COMPLETED\n");
            printf("NO Memory Access Involved \n Passing ALU output \n Data out/in : %d\n",pr.pr_mx.data);
            break;
        
        case 'X':
            printf("===================================\n");
            printf("EXCEPTION STAGE COMPLETED\n");
            break;
        
        case 'W':
            printf("===================================\n");
            printf("WRITE BACK STAGE COMPLETED\n");
            printf("Written %d to Register %d\n",pr.pr_xwb.data,pr.pr_xwb.rd);
            break;

        default:
            break;
    }
}
