#include "core.h"

Core::Core()
{
    regs.init_reg_file();
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x09200000);  //SETHI
    // icache.push_back(0x10800001);  //Branch Always
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

    while(regs.pc < 3)
    {        
        //Write Back
        wb.wrt_back(pr,regs);
        print_pregs(pr,'W');

        //Exception
        x.exception(pr);
        print_pregs(pr,'X');

        //Memory Access
        m.mem_access(pr,dcache);
        print_pregs(pr,'M');


        //Execute
        e.execute(pr,regs.pc);
        print_pregs(pr,'E');

        //Register Access
        ra.reg_access(pr,regs);
        print_pregs(pr,'R');

        //Decode
        d.decode(pr);
        print_pregs(pr,'D');

        pr.f.pc = regs.pc;
        pr.f.valid = true;
        //Fetch
        f.fetch(pr, icache);
        print_pregs(pr,'F');

        regs.pc++;
    }
    
}

void print_pregs(PipeRegister pr,char s)
{
    switch (s)
    {
        case 'F':
            printf("===================================\n");
            printf("FETCH STAGe\n");
            printf("Instruction : %x\n",pr.d.instr);
            printf("PC : %d\n",pr.d.pc);
            break;

        case 'D':
            printf("===================================\n");
            printf("DECODE STAGE COMPLETED\n");
            printf(" Source Register A  : %d\n",pr.a.rs1);
            printf(" Source Register B  : %d\n",pr.a.rs2);
            printf(" Destination Register : %d\n",pr.a.rd);
            break;
        
        case 'R':
            printf("===================================\n");
            printf("REGISTER ACCESS COMPLETED\n");
            printf(" Operand 1 : %d\n",pr.e.operand1);
            printf(" Operand 2 : %d\n",pr.e.operand2);
            break;
        
        case 'E':
            printf("===================================\n");
            printf("EXECUTE STAGE COMPLETED\n");
            printf("ALU output : %d\n",pr.m.ares);
            break;
        
        case 'M':
            printf("===================================\n");
            printf("MEMORY ACCESS COMPLETED\n");
            printf("NO Memory Access Involved \n Passing ALU output \n Data out/in : %d\n",pr.x.data);
            break;
        
        case 'X':
            printf("===================================\n");
            printf("EXCEPTION STAGE COMPLETED\n");
            break;
        
        case 'W':
            printf("===================================\n");
            printf("WRITE BACK STAGE COMPLETED\n");
            printf("Written %d to Register %d\n",pr.w.data,pr.w.rd);
            printf("No.of Cycles Taken : %d\n",pr.w.instr.cycles);
            break;

        default:
            break;
    }
}
