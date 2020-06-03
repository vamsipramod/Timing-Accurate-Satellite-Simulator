#include "mem.h"


Memory::Memory(std::vector <uint32_t> text,std::vector <uint32_t> data)
{
    this->text = text;
    this->data = data;
}

std::pair<uint32_t, bool> Memory::get_instruction(mem_addr addr)
{
    uint32_t inst=0;
    uint32_t index = addr/4;
    std::cout<<index<<"\t"<<text.size()<<"\n";
    if( index >= text.size())
    {
        NANO_LOG(DEBUG,"Memory address to get_instruction() is out of bound [at Text Section]\n");
        return std::make_pair(inst,false);
    }
        
    else
    {
        inst = text.at(index);
        return std::make_pair(inst,true);
    }
    
}

void Memory::set_word(mem_addr addr,uint32_t value)
{
    if( addr/4 >= text.size())
        NANO_LOG(DEBUG,"Memory address to get_instruction() is out of bound [at Text Section]\n");
    
    else
    {
        text[addr/4] = value;
    }
}
