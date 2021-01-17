/*
 * http://wiki.xentax.com/index.php/Wwise_SoundBank_(*.bnk)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HIRC.h"


#define COPY(var, source, type, ifp)  memcpy(&var, source+ifp, sizeof(type)); ifp += sizeof(type);

short UINT32_S = sizeof(u_int32_t);
u_int8_t* readfile(FILE* fp, size_t *size);
void extract_sections(u_int8_t *data, size_t size);


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

        else if( strcmp("HIRC", identifier) == 0 )
        {
            size_t section_start = ifp;

            ifp += 4;
            unsigned section_size;
            COPY(section_size, data, unsigned, ifp);

            HIRC(data, section_start, section_size);

            ifp = section_start + section_size;
        }
    }
}


void HIRC(u_int8_t *data, unsigned start, unsigned size)
{
    /*
     * uint32: number of objects
     * FOR EACH (object) {
     *     byte: single byte identifying type of object
     *     uint32: length of object section (= 4-byte id field and additional bytes)
     *     uint32: id of this object
     *     byte[]: additional bytes, depending on type of object and section length
     * } END FOR
     */
    
    int ifp = start + 4 + UINT32_S;

    unsigned number_of_objects;
    COPY(number_of_objects, data, unsigned, ifp);


#ifdef DEBUG
    printf("\nSection: HIRC @ %u\n", start);
    printf("Section size: %u\n", size);
    printf("Number of objects: %u\n", number_of_objects);
#endif

    for(int i=0; i<number_of_objects; i++)
    {
        u_int8_t obj_type;
        unsigned obj_size, obj_id, obj_start=ifp;

        COPY(obj_type, data, u_int8_t, ifp);
        COPY(obj_size, data, unsigned, ifp);
        int data_start = ifp; // obj_size doesn't include type and size fields, so start here
        COPY(obj_id, data, unsigned, ifp);
        

        switch(obj_type)
        {
            case SETTINGS:
                PRINT_OBJ(i, obj_start, SETTINGS);
                HIRC_SETTINGS(data, obj_start);
                break;
            case SFX_OR_VOICE:
                PRINT_OBJ(i, obj_start, SFX_OR_VOICE);
                HIRC_SFX_OR_VOICE(data, obj_start);
                break;
            case EVENT_ACTION:
                PRINT_OBJ(i, obj_start, EVENT_ACTION);
                HIRC_EVENT_ACTION(data, obj_start);
                break;
            case EVENT:
                PRINT_OBJ(i, obj_start, EVENT);
                HIRC_EVENT(data, obj_start);
                break;
            case RANDOM_OR_SEQUENCE_CONTAINER:
                PRINT_OBJ(i, obj_start, RANDOM_OR_SEQUENCE_CONTAINER);
                HIRC_RANDOM_OR_SEQUENCE_CONTAINER(data, obj_start);
                break;
            case SWITCH_CONTAINER:
                PRINT_OBJ(i, obj_start, SWITCH_CONTAINER);
                HIRC_SWITCH_CONTAINER(data, obj_start);
                break;
            case ACTOR_MIXER:
                PRINT_OBJ(i, obj_start, ACTOR_MIXER);
                HIRC_ACTOR_MIXER(data, obj_start);
                break;
            case AUDIO_BUS:
                PRINT_OBJ(i, obj_start, AUDIO_BUS);
                HIRC_AUDIO_BUS(data, obj_start);
                break;
            case BLEND_CONTAINER:
                PRINT_OBJ(i, obj_start, BLEND_CONTAINER);
                HIRC_BLEND_CONTAINER(data, obj_start);
                break;
            case MUSIC_SEGMENT:
                PRINT_OBJ(i, obj_start, MUSIC_SEGMENT);
                HIRC_MUSIC_SEGMENT(data, obj_start);
                break;
            case MUSIC_TRACK:
                PRINT_OBJ(i, obj_start, MUSIC_TRACK);
                HIRC_MUSIC_TRACK(data, obj_start);
                break;
            case MUSIC_SWITCH_CONTAINER:
                PRINT_OBJ(i, obj_start, MUSIC_SWITCH_CONTAINER);
                HIRC_MUSIC_SWITCH_CONTAINER(data, obj_start);
                break;
            case MUSIC_PLAYLIST_CONTAINER:
                PRINT_OBJ(i, obj_start, MUSIC_PLAYLIST_CONTAINER);
                HIRC_MUSIC_PLAYLIST_CONTAINER(data, obj_start);
                break;
            case ATTENUATION:
                PRINT_OBJ(i, obj_start, ATTENUATION);
                HIRC_ATTENUATION(data, obj_start);
                break;
            case DIALOGUE_EVENT:
                PRINT_OBJ(i, obj_start, DIALOGUE_EVENT);
                HIRC_DIALOGUE_EVENT(data, obj_start);
                break;
            case MOTION_BUS:
                PRINT_OBJ(i, obj_start, MOTION_BUS);
                HIRC_MOTION_BUS(data, obj_start);
                break;
            case MOTION_FX:
                PRINT_OBJ(i, obj_start, MOTION_FX);
                HIRC_MOTION_FX(data, obj_start);
                break;
            case EFFECT:
                PRINT_OBJ(i, obj_start, EFFECT);
                HIRC_EFFECT(data, obj_start);
                break;
            case AUXILIARY_BUS:
                PRINT_OBJ(i, obj_start, AUXILIARY_BUS);
                HIRC_AUXILIARY_BUS(data, obj_start);
                break;
        }

        ifp = data_start + obj_size;
    }
}