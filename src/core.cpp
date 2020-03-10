#include "core.h"

Core::Core(string i)
{   
    this->__id__ = "cpu" + i;
    regs.init_reg_file();
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x09200000);  //SETHI
    icache.push_back(0x10800001);  //Branch Always
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x82008003); //ADD
    icache.push_back(0x82008003); //ADD
    
    pc = 0;
    regs.reg(1,10);
    regs.reg(2,20);
    regs.reg(3,30);
    regs.reg(4,40);
    regs.reg(5,50);

    f = new Fetch(this->__id__);
    d = new Decode(this->__id__);
    ra = new Reg_access(this->__id__);
    e = new Execute(this->__id__);
    m = new Mem_access(this->__id__);
    x = new Exception(this->__id__);
    wb = new Wrt_back(this->__id__);
}

void Core:: pipeline()
{
    bool run = true;
    bool flush = false;
    uint32_t cyc = 1;

    NANO_LOG(NOTICE,"Pipeline Started\n");

    while(run)
    { 
        NANO_LOG(DEBUG,"=========================CYCLE %d ============================\n",cyc++);    
        
        //Write Back
        wb->wrt_back(pr,regs);

        //Exception
        x->exception(pr);

        //Memory Access
        m->mem_access(pr,dcache);

        //Execute
        e->execute(pr,pc,flush);

        if(flush)
            { flush = false; continue; }

        //Register Access
        ra->reg_access(pr,regs);
       
        //Decode
        d->decode(pr);

        
        if(pc >= icache.size())
            pr.f.valid = 0;
        else
            pr.f.valid = 1;

        pr.f.pc = pc;
        //Fetch
        f->fetch(pr, icache);

        pc++;
        run = pr.f.valid | pr.d.valid | pr.a.valid | pr.e.valid | pr.m.valid | pr.x.valid | pr.w.valid;
    }
    
}