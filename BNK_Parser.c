/*
 * http://wiki.xentax.com/index.php/Wwise_SoundBank_(*.bnk)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BNK_Parser.h"


u_int8_t* readfile(FILE* fp);
void extract_sections(u_int8_t *data);
short UINT32_S = sizeof(u_int32_t);


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

    u_int8_t* data = readfile(fp);
    fclose(fp);
    
    extract_sections(data);
    free(data);
}


u_int8_t* readfile(FILE* fp)
{
    g_fsize = 0;
    while( getc(fp) != -1 ) g_fsize++;
    
#ifdef DEBUG
    printf("Filesize: %lu\n", g_fsize);
#endif

    u_int8_t *data = malloc(sizeof(u_int8_t) * g_fsize);

    rewind(fp);
    fread(data, g_fsize, 1, fp);
    
#ifdef DEBUG
    printf("Loaded file successfully\n");
#endif

    return data;
}


void extract_sections(u_int8_t *data)
{
#ifdef DEBUG
    printf("Reading sections\n");
#endif

    for(g_ifp=0; g_ifp < g_fsize; g_ifp++)
    {
        char identifier[4] = {data[g_ifp], data[g_ifp+1], data[g_ifp+2], data[g_ifp+3]};
        
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

            BKHD_Section* bkhd = malloc(sizeof(BKHD_Section));
            
            size_t section_start = g_ifp;
            
            g_ifp += 4;

            bkhd->location = section_start;
            COPY(bkhd->size, data, unsigned, g_ifp);
            COPY(bkhd->version, data, unsigned, g_ifp);
            COPY(bkhd->id, data, unsigned, g_ifp);

            g_bnk.BKHD = bkhd;

#ifdef DEBUG
            printf("\nSection: %s @ %ld\n", identifier, section_start);
            printf("Section size: %u\n", g_bnk.BKHD->size);
            printf("BNK version: %u\n", g_bnk.BKHD->version);
            printf("File ID: %u\n", g_bnk.BKHD->id);
#endif
            g_ifp = section_start + bkhd->size;
        }

        else if( strcmp("DIDX", identifier) == 0 ) puts("DIDX");
        else if( strcmp("DATA", identifier) == 0 ) puts("DATA");
        else if( strcmp("ENVS", identifier) == 0 ) puts("ENVS");
        else if( strcmp("FXPR", identifier) == 0 ) puts("FXPR");

        else if( strcmp("HIRC", identifier) == 0 )
        {
            size_t section_start = g_ifp;
            g_ifp += 4;
            unsigned section_size;
            COPY(section_size, data, unsigned, g_ifp);
            HIRC(data, section_start, section_size);
            g_ifp = section_start + section_size;
        }

        else if( strcmp("STID", identifier) == 0 ) puts("STID");
        else if( strcmp("STMG", identifier) == 0 ) puts("STMG");
    }
}