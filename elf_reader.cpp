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

        while ( n < shdr.sh_size && ( data = elf_getdata(scn ,data)) != NULL )
        {
            uint64_t i=0,buff_size=0;
            int32_t *p = (int32_t *) data->d_buf;


            buff_size = data->d_size;
            // fprintf(output_file, "start address : %p\t \t End address : %p\n",p,p+buff_size);

            int counter = 0;
            int32_t* curr_instruction = (int32_t *)malloc(sizeof(int32_t));
            char* current = curr_instruction;
            for (i = 0; i < buff_size; ++i)
            {    
                if(p == NULL)
                {
                    printf( "Err: NULL address\n");
                    break;
                }
                counter++;
                sprintf(current,"%x", p[i]);
                current += 2;

                if(counter == 4)
                {   
                    counter = 0;
                    instructions.push_back(curr_instruction);
                    
                    curr_instruction = (char *)malloc(8*sizeof(char));
                    current = curr_instruction;
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

char* elf::get_instruciton()
{
    if(instructions.size() > 0 && current_instruction_index < instructions.size())
    {
        return instructions[current_instruction_index];
    }

    else if(instructions.size() == 0)
    {
        return (char *)"Error: No instructions, Read the instructions and try again";
    }

    else
    {
        return (char *)"Reached the end of instructions";
    }
    
}

void elf::print_instructions()
{
    for(auto i=instructions.begin();i!=instructions.end();i++)
    {
        char* inst = *i;
        printf("%s\n",inst);
    }
}

void elf::write_instructions()
{
    FILE *fd;
    char output_file[] = "instructions.txt";
    fd = fopen(output_file,"w");

    if(fd == NULL)
        err(EXIT_FAILURE,"Failure in opening the file : %s",output_file);
    
    for(auto i=instructions.begin();i!=instructions.end();i++)
    {
        char *curr_instruction = *i;
        fprintf(fd,"%s\n",curr_instruction);
    }
    fclose(fd);
}

