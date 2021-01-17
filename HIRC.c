#include "HIRC.h"
#include "BNK_Parser.h"

void HIRC_SETTINGS(u_int8_t* data, int ifp);
void HIRC_SFX_OR_VOICE(u_int8_t* data, int ifp);
void HIRC_EVENT_ACTION(u_int8_t* data, int ifp);
void HIRC_EVENT(u_int8_t* data, int ifp);
void HIRC_RANDOM_OR_SEQUENCE_CONTAINER(u_int8_t* data, int ifp);
void HIRC_SWITCH_CONTAINER(u_int8_t* data, int ifp);
void HIRC_ACTOR_MIXER(u_int8_t* data, int ifp);
void HIRC_AUDIO_BUS(u_int8_t* data, int ifp);
void HIRC_BLEND_CONTAINER(u_int8_t* data, int ifp);
void HIRC_MUSIC_SEGMENT(u_int8_t* data, int ifp);
void HIRC_MUSIC_TRACK(u_int8_t* data, int ifp);
void HIRC_MUSIC_SWITCH_CONTAINER(u_int8_t* data, int ifp);
void HIRC_MUSIC_PLAYLIST_CONTAINER(u_int8_t* data, int ifp);
void HIRC_ATTENUATION(u_int8_t* data, int ifp);
void HIRC_DIALOGUE_EVENT(u_int8_t* data, int ifp);
void HIRC_MOTION_BUS(u_int8_t* data, int ifp);
void HIRC_MOTION_FX(u_int8_t* data, int ifp);
void HIRC_EFFECT(u_int8_t* data, int ifp);
void HIRC_AUXILIARY_BUS(u_int8_t* data, int ifp);


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


void HIRC_SETTINGS(u_int8_t* data, int ifp){}
void HIRC_SFX_OR_VOICE(u_int8_t* data, int ifp){}
void HIRC_EVENT_ACTION(u_int8_t* data, int ifp){}
void HIRC_EVENT(u_int8_t* data, int ifp){}
void HIRC_RANDOM_OR_SEQUENCE_CONTAINER(u_int8_t* data, int ifp){}
void HIRC_SWITCH_CONTAINER(u_int8_t* data, int ifp){}
void HIRC_ACTOR_MIXER(u_int8_t* data, int ifp){}
void HIRC_AUDIO_BUS(u_int8_t* data, int ifp){}
void HIRC_BLEND_CONTAINER(u_int8_t* data, int ifp){}
void HIRC_MUSIC_SEGMENT(u_int8_t* data, int ifp){}
void HIRC_MUSIC_TRACK(u_int8_t* data, int ifp){}
void HIRC_MUSIC_SWITCH_CONTAINER(u_int8_t* data, int ifp){}
void HIRC_MUSIC_PLAYLIST_CONTAINER(u_int8_t* data, int ifp){}
void HIRC_ATTENUATION(u_int8_t* data, int ifp){}
void HIRC_DIALOGUE_EVENT(u_int8_t* data, int ifp){}
void HIRC_MOTION_BUS(u_int8_t* data, int ifp){}
void HIRC_MOTION_FX(u_int8_t* data, int ifp){}
void HIRC_EFFECT(u_int8_t* data, int ifp){}
void HIRC_AUXILIARY_BUS(u_int8_t* data, int ifp){}