/*
 * http://wiki.xentax.com/index.php/Wwise_SoundBank_(*.bnk)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BNK_Parser.h"
#include "HIRC.h"


u_int8_t* readfile(FILE* fp, size_t *size);
void extract_sections(u_int8_t *data, size_t size);
short UINT32_S = sizeof(u_int32_t);


void HIRC(u_int8_t *data, unsigned start, unsigned size);


int main(int argc, char** argv)
{
    if( argc < 2 )
    {
        puts("Please enter a filename");
        exit(1);
    }

    FILE* fp = fopen(argv[1], "rb");
    if( !fp )
    {
        puts("Error opening file");
        exit(1);
    }

    
    size_t size;
    u_int8_t* data = readfile(fp, &size);
    fclose(fp);
    
    extract_sections(data, size);

    free(data);
}


u_int8_t* readfile(FILE* fp, size_t *size)
{
    *size = 0;
    while( getc(fp) != -1 ) (*size)++;
    
#ifdef DEBUG
    printf("Filesize: %lu\n", *size);
#endif

    u_int8_t *data = malloc(sizeof(u_int8_t) * *size);

    rewind(fp);
    fread(data, *size, 1, fp);
    
#ifdef DEBUG
    printf("Loaded file successfully\n");
#endif

    return data;
}


void extract_sections(u_int8_t *data, size_t size)
{
#ifdef DEBUG
    printf("Reading sections\n");
#endif

    for(unsigned ifp=0; ifp < size; ifp++)
    {
        char identifier[4] = {data[ifp], data[ifp+1], data[ifp+2], data[ifp+3]};
        
        if( strcmp("BKHD", identifier) == 0 )
        {
            /*
             * 42 4B 48 44 -- BKHD                      width: 4
             * uint32: length of section                width: 8
             * uint32: version number of this SoundBank
             * uint32: id of this SoundBank
             * uint32: always zero
             * uint32: always zero
            */
            size_t section_start = ifp;
            unsigned section_size, version, file_id;
            ifp += 4;
            COPY(section_size, data, unsigned, ifp);
            COPY(version, data, unsigned, ifp);
            COPY(file_id, data, unsigned, ifp);

#ifdef DEBUG
            printf("\nSection: %s @ %ld\n", identifier, section_start);
            printf("Section size: %u\n", section_size);
            printf("BNK version: %u\n", version);
            printf("File ID: %u\n", file_id);
#endif
            ifp = section_start + section_size;
        }

        else if( strcmp("DIDX", identifier) == 0 ) puts("DIDX");
        else if( strcmp("DATA", identifier) == 0 ) puts("DATA");
        else if( strcmp("ENVS", identifier) == 0 ) puts("ENVS");
        else if( strcmp("FXPR", identifier) == 0 ) puts("FXPR");

        else if( strcmp("HIRC", identifier) == 0 )
        {
            size_t section_start = ifp;
            ifp += 4;
            unsigned section_size;
            COPY(section_size, data, unsigned, ifp);
            HIRC(data, section_start, section_size);
            ifp = section_start + section_size;
        }

        else if( strcmp("STID", identifier) == 0 ) puts("STID");
        else if( strcmp("STMG", identifier) == 0 ) puts("STMG");

    }
}