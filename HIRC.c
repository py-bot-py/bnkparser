#include "BNK_Parser.h"

void PARSE_SETTINGS(u_int8_t* data, unsigned ifp){}
void PARSE_SFX_OR_VOICE(u_int8_t* data, unsigned ifp){}
void PARSE_EVENT_ACTION(u_int8_t* data, unsigned ifp){}
void PARSE_EVENT(u_int8_t* data, unsigned ifp){}
void PARSE_RANDOM_OR_SEQUENCE_CONTAINER(u_int8_t* data, unsigned ifp){}
void PARSE_SWITCH_CONTAINER(u_int8_t* data, unsigned ifp){}
void PARSE_ACTOR_MIXER(u_int8_t* data, unsigned ifp){}
void PARSE_AUDIO_BUS(u_int8_t* data, unsigned ifp){}
void PARSE_BLEND_CONTAINER(u_int8_t* data, unsigned ifp){}
void PARSE_MUSIC_SEGMENT(u_int8_t* data, unsigned ifp){}
void PARSE_MUSIC_TRACK(u_int8_t* data, unsigned ifp){}
void PARSE_MUSIC_SWITCH_CONTAINER(u_int8_t* data, unsigned ifp){}
void PARSE_MUSIC_PLAYLIST_CONTAINER(u_int8_t* data, unsigned ifp){}
void PARSE_ATTENUATION(u_int8_t* data, unsigned ifp){}
void PARSE_DIALOGUE_EVENT(u_int8_t* data, unsigned ifp){}
void PARSE_MOTION_BUS(u_int8_t* data, unsigned ifp){}
void PARSE_MOTION_FX(u_int8_t* data, unsigned ifp){}
void PARSE_EFFECT(u_int8_t* data, unsigned ifp){}
void PARSE_AUXILIARY_BUS(u_int8_t* data, unsigned ifp){}


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
    
    unsigned ifp = start + 4 + UINT32_S;

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
                PARSE_SETTINGS(data, obj_start);
                break;
            case SFX_OR_VOICE:
                PRINT_OBJ(i, obj_start, SFX_OR_VOICE);
                PARSE_SFX_OR_VOICE(data, obj_start);
                break;
            case EVENT_ACTION:
                PRINT_OBJ(i, obj_start, EVENT_ACTION);
                PARSE_EVENT_ACTION(data, obj_start);
                break;
            case EVENT:
                PRINT_OBJ(i, obj_start, EVENT);
                PARSE_EVENT(data, obj_start);
                break;
            case RANDOM_OR_SEQUENCE_CONTAINER:
                PRINT_OBJ(i, obj_start, RANDOM_OR_SEQUENCE_CONTAINER);
                PARSE_RANDOM_OR_SEQUENCE_CONTAINER(data, obj_start);
                break;
            case SWITCH_CONTAINER:
                PRINT_OBJ(i, obj_start, SWITCH_CONTAINER);
                PARSE_SWITCH_CONTAINER(data, obj_start);
                break;
            case ACTOR_MIXER:
                PRINT_OBJ(i, obj_start, ACTOR_MIXER);
                PARSE_ACTOR_MIXER(data, obj_start);
                break;
            case AUDIO_BUS:
                PRINT_OBJ(i, obj_start, AUDIO_BUS);
                PARSE_AUDIO_BUS(data, obj_start);
                break;
            case BLEND_CONTAINER:
                PRINT_OBJ(i, obj_start, BLEND_CONTAINER);
                PARSE_BLEND_CONTAINER(data, obj_start);
                break;
            case MUSIC_SEGMENT:
                PRINT_OBJ(i, obj_start, MUSIC_SEGMENT);
                PARSE_MUSIC_SEGMENT(data, obj_start);
                break;
            case MUSIC_TRACK:
                PRINT_OBJ(i, obj_start, MUSIC_TRACK);
                PARSE_MUSIC_TRACK(data, obj_start);
                break;
            case MUSIC_SWITCH_CONTAINER:
                PRINT_OBJ(i, obj_start, MUSIC_SWITCH_CONTAINER);
                PARSE_MUSIC_SWITCH_CONTAINER(data, obj_start);
                break;
            case MUSIC_PLAYLIST_CONTAINER:
                PRINT_OBJ(i, obj_start, MUSIC_PLAYLIST_CONTAINER);
                PARSE_MUSIC_PLAYLIST_CONTAINER(data, obj_start);
                break;
            case ATTENUATION:
                PRINT_OBJ(i, obj_start, ATTENUATION);
                PARSE_ATTENUATION(data, obj_start);
                break;
            case DIALOGUE_EVENT:
                PRINT_OBJ(i, obj_start, DIALOGUE_EVENT);
                PARSE_DIALOGUE_EVENT(data, obj_start);
                break;
            case MOTION_BUS:
                PRINT_OBJ(i, obj_start, MOTION_BUS);
                PARSE_MOTION_BUS(data, obj_start);
                break;
            case MOTION_FX:
                PRINT_OBJ(i, obj_start, MOTION_FX);
                PARSE_MOTION_FX(data, obj_start);
                break;
            case EFFECT:
                PRINT_OBJ(i, obj_start, EFFECT);
                PARSE_EFFECT(data, obj_start);
                break;
            case AUXILIARY_BUS:
                PRINT_OBJ(i, obj_start, AUXILIARY_BUS);
                PARSE_AUXILIARY_BUS(data, obj_start);
                break;
        }

        ifp = data_start + obj_size;
    }
}