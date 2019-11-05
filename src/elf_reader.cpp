#include "elf_reader.h"

elf::elf(char *input_file)
{
    if ( elf_version ( EV_CURRENT ) == EV_NONE )
        errx ( EXIT_FAILURE , " ELF library initialization  failed : %s " , elf_errmsg ( -1));

    int fd=0;
    if (( fd = open ( input_file , O_RDONLY , 0)) < 0)
        err ( EXIT_FAILURE , " open  %s  failed " , input_file);

    if (( e = elf_begin ( fd , ELF_C_READ , NULL )) == NULL )
        errx ( EXIT_FAILURE , " elf_begin () failed : %s . " ,elf_errmsg ( -1));
    
    if ( elf_kind ( e ) != ELF_K_ELF )
        errx ( EXIT_FAILURE , " %s is not an ELF object . " ,input_file);

    if ( elf_getshdrstrndx (e , & shstrndx ) != 0)
            errx ( EXIT_FAILURE , " elf_getshdrstrndx () failed : %s . " ,elf_errmsg ( -1));  

}

void elf::read_elf_instruction()
{
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    while ((scn = elf_nextscn(e,scn)) != NULL)
    { 
        if (gelf_getshdr (scn ,&shdr) != &shdr)
            errx(EXIT_FAILURE ," getshdr () failed : %s . ",elf_errmsg ( -1));

        Elf_Data *data = NULL;
        size_t n = 0;
		int shift =24;
		uint32_t instr = 0;

        while ( n < shdr.sh_size && ( data = elf_getdata(scn ,data)) != NULL )
        {
            uint32_t i=0,buff_size=0;
            unsigned char *p = (unsigned char *) data->d_buf;


            buff_size = data->d_size;

            for (i = 0; i < buff_size; ++i)
            {    
                if(p == NULL)
                {
                    printf( "Err: NULL address\n");
                    break;
                }

			    uint32_t curr_byte = p[i];
                
                curr_byte <<= shift;
                shift -= 8;

                instr = instr | curr_byte;

                if(shift < 0)
                {
                    shift = 24;
                    instructions.push_back(instr);
                    instr = 0;
                }
            }
        }
        break;
    }
}

void elf::print_section_header(Elf_Scn *scn)
{
    GElf_Shdr hdr;
    char* section_name;

    if (gelf_getshdr (scn ,&hdr) != &hdr)
        errx(EXIT_FAILURE ," getshdr () failed : %s . ",elf_errmsg ( -1));

    if ((section_name = elf_strptr(e,shstrndx,hdr.sh_name))== NULL)
        errx(EXIT_FAILURE ," elf_strptr () failed : %s . ",elf_errmsg ( -1));

    ( void ) printf(" Section %-4.4jd %s \n " ,( uintmax_t )elf_ndxscn( scn ),section_name);     

    PRINT_FIELD(sh_name);            NL();
    // print_ptype(phdr.p_type);       NL();
    PRINT_FIELD(sh_flags);          NL();
    PRINT_FIELD(sh_addr);           NL();
    PRINT_FIELD(sh_offset);           NL();
    PRINT_FIELD(sh_size);          NL();
    PRINT_FIELD(sh_link);           NL();
    PRINT_FIELD(sh_info);           NL();
    PRINT_FIELD(sh_addralign);           NL();
    PRINT_FIELD(sh_entsize);           NL();
    printf("====================\n");
}

uint32_t elf::get_instruciton()
{
    if(instructions.size() > 0 && current_instruction_index < instructions.size())
    {
        return instructions[current_instruction_index];
    }

    else if(instructions.size() == 0)
    {
        return 0;
    }

    else
    {
        return 0;
    }
    
}

void elf::print_instructions()
{
    for(auto i=instructions.begin();i!=instructions.end();i++)
    {
        printf("%8.8x\n",*i);
    }
}

void elf::write_instructions(char output_file[])
{
    FILE *fd;
    
    fd = fopen(output_file,"w");

    if(fd == NULL)
        err(EXIT_FAILURE,"Failure in opening the file : %s",output_file);
    
    for(auto i=instructions.begin();i!=instructions.end();i++)
    {
        fprintf(fd,"%8.8x\n",*i);
    }
    fclose(fd);
}
