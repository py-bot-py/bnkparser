#include "BNK_Parser.h"


unsigned ifp;


void PARSE_SETTINGS(u_int8_t* data, unsigned size)
{
    HIRC_SETTINGS *settings = malloc(sizeof(HIRC_SETTINGS));
    settings->size = size;

    COPY(settings->number_of_settings, data, unsigned, ifp);
}


void PARSE_SFX_OR_VOICE(u_int8_t* data, unsigned size){}
void PARSE_EVENT_ACTION(u_int8_t* data, unsigned size){}
void PARSE_EVENT(u_int8_t* data, unsigned size){}
void PARSE_RANDOM_OR_SEQUENCE_CONTAINER(u_int8_t* data, unsigned size){}
void PARSE_SWITCH_CONTAINER(u_int8_t* data, unsigned size){}
void PARSE_ACTOR_MIXER(u_int8_t* data, unsigned size){}
void PARSE_AUDIO_BUS(u_int8_t* data, unsigned size){}
void PARSE_BLEND_CONTAINER(u_int8_t* data, unsigned size){}

void PARSE_MUSIC_SEGMENT(u_int8_t* data, unsigned size)
{
    HIRC_MUSIC_SEGMENT *music_segment = malloc(sizeof(HIRC_MUSIC_SEGMENT));
    music_segment->size = size;

    COPY(music_segment->id, data, u_int32_t, ifp);

    // SOUND SETTINGS
    SOUND_STRUCTURE *ss = malloc(sizeof(SOUND_STRUCTURE));

    COPY(ss->override_parent_settings, data, bool, ifp);
    COPY(ss->number_of_effects, data, u_int8_t, ifp);

    if( ss->number_of_effects > 0 )
    {
        COPY(ss->effect_mask, data, byte, ifp);
        ss->effects = malloc(sizeof(SOUND_EFFECT*) * ss->number_of_effects);
        
        for( int i=0; i<ss->number_of_effects; i++ )
        {
            ss->effects[i] = malloc(sizeof(SOUND_EFFECT));
            COPY(ss->effects[i]->index, data, byte, ifp);
            COPY(ss->effects[i]->id, data, u_int32_t, ifp);
            ifp += sizeof(u_int8_t) * 2;
        }
    }

    COPY(ss->output_bus, data, u_int32_t, ifp);
    COPY(ss->parent_id, data, u_int32_t, ifp);
    COPY(ss->override_parent, data, bool, ifp);
    COPY(ss->offset_priority_activated, data, bool, ifp);
    COPY(ss->number_of_params, data, u_int8_t, ifp);

    // Parameter types
    ss->param_types = malloc(sizeof(u_int8_t*) * ss->number_of_params);
    for( int i=0; i<ss->number_of_params; i++ )
    {
        COPY(ss->param_types, data, u_int8_t, ifp);
    }
    
    // Parameter values
    ss->param_vals = malloc(sizeof(union SS_PARAM) * ss->number_of_params);
    for( int i=0; i<ss->number_of_params; i++ )
    {
        if( ss->param_types[i] == 0x07 )
        {
            COPY(ss->param_vals[i], data, u_int32_t, ifp);
        } else
        {
            COPY(ss->param_vals[i], data, float, ifp);
        }
    }

    u_int8_t sanity_check;
    COPY(sanity_check, data, u_int8_t, ifp); // Unknown null byte
    if( sanity_check )
        printf("BURN\n");

    COPY(ss->has_positioning_section, data, bool, ifp);
    if( ss->has_positioning_section )
    {
        printf("Positioning section: %x\n", ss->has_positioning_section);
        ss->p_section = malloc(sizeof(POSISTIONING_SECTION));
        COPY(ss->p_section->type, data, u_int8_t, ifp);

        if( ss->p_section->type == 0 )
            printf("2d\n");
        else if( ss->p_section->type == 0x1 )
            printf("3d\n");
        else
            // LOL GET REKT
            printf("You dun fucked: %x\n", ss->p_section->type);
    }

}

void PARSE_MUSIC_TRACK(u_int8_t* data, unsigned size){}

void PARSE_MUSIC_SWITCH_CONTAINER(u_int8_t* data, unsigned size){}
void PARSE_MUSIC_PLAYLIST_CONTAINER(u_int8_t* data, unsigned size){}
void PARSE_ATTENUATION(u_int8_t* data, unsigned size){}
void PARSE_DIALOGUE_EVENT(u_int8_t* data, unsigned size){}
void PARSE_MOTION_BUS(u_int8_t* data, unsigned size){}
void PARSE_MOTION_FX(u_int8_t* data, unsigned size){}
void PARSE_EFFECT(u_int8_t* data, unsigned size){}
void PARSE_AUXILIARY_BUS(u_int8_t* data, unsigned size){}



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
    
    ifp = start + 4 + UINT32_S;

    unsigned number_of_objects;
    COPY(number_of_objects, data, unsigned, ifp);


#ifdef DEBUG
    printf("\nSection: HIRC @ %u\n", start);
    printf("Section size: %u\n", size);
    printf("Number of objects: %u\n", number_of_objects);
#endif

    for(int i=1; i<number_of_objects+1; i++)
    {
        u_int8_t obj_type;
        unsigned obj_start, obj_size;

        obj_start = ifp;
        COPY(obj_type, data, u_int8_t, ifp);
        COPY(obj_size, data, u_int32_t, ifp);
        int data_start = ifp; // obj_size doesn't include type and size fields, so start here        

        switch(obj_type)
        {
            case SETTINGS:
                // PRINT_OBJ(i, number_of_objects, obj_start, SETTINGS);
                PARSE_SETTINGS(data, obj_size);
                break;
            case SFX_OR_VOICE:
                // PRINT_OBJ(i, number_of_objects, obj_start, SFX_OR_VOICE);
                PARSE_SFX_OR_VOICE(data, obj_size);
                break;
            case EVENT_ACTION:
                // PRINT_OBJ(i, number_of_objects, obj_start, EVENT_ACTION);
                PARSE_EVENT_ACTION(data, obj_size);
                break;
            case EVENT:
                // PRINT_OBJ(i, number_of_objects, obj_start, EVENT);
                PARSE_EVENT(data, obj_size);
                break;
            case RANDOM_OR_SEQUENCE_CONTAINER:
                // PRINT_OBJ(i, number_of_objects, obj_start, RANDOM_OR_SEQUENCE_CONTAINER);
                PARSE_RANDOM_OR_SEQUENCE_CONTAINER(data, obj_size);
                break;
            case SWITCH_CONTAINER:
                // PRINT_OBJ(i, number_of_objects, obj_start, SWITCH_CONTAINER);
                PARSE_SWITCH_CONTAINER(data, obj_size);
                break;
            case ACTOR_MIXER:
                // PRINT_OBJ(i, number_of_objects, obj_start, ACTOR_MIXER);
                PARSE_ACTOR_MIXER(data, obj_size);
                break;
            case AUDIO_BUS:
                // PRINT_OBJ(i, number_of_objects, obj_start, AUDIO_BUS);
                PARSE_AUDIO_BUS(data, obj_size);
                break;
            case BLEND_CONTAINER:
                // PRINT_OBJ(i, number_of_objects, obj_start, BLEND_CONTAINER);
                PARSE_BLEND_CONTAINER(data, obj_size);
                break;
            case MUSIC_SEGMENT:
                // PRINT_OBJ(i, number_of_objects, obj_start, MUSIC_SEGMENT);
                PARSE_MUSIC_SEGMENT(data, obj_size);
                break;
            case MUSIC_TRACK:
                // PRINT_OBJ(i, number_of_objects, obj_start, MUSIC_TRACK);
                PARSE_MUSIC_TRACK(data, obj_size);
                break;
            case MUSIC_SWITCH_CONTAINER:
                // PRINT_OBJ(i, number_of_objects, obj_start, MUSIC_SWITCH_CONTAINER);
                PARSE_MUSIC_SWITCH_CONTAINER(data, obj_size);
                break;
            case MUSIC_PLAYLIST_CONTAINER:
                // PRINT_OBJ(i, number_of_objects, obj_start, MUSIC_PLAYLIST_CONTAINER);
                PARSE_MUSIC_PLAYLIST_CONTAINER(data, obj_size);
                break;
            case ATTENUATION:
                // PRINT_OBJ(i, number_of_objects, obj_start, ATTENUATION);
                PARSE_ATTENUATION(data, obj_size);
                break;
            case DIALOGUE_EVENT:
                // PRINT_OBJ(i, number_of_objects, obj_start, DIALOGUE_EVENT);
                PARSE_DIALOGUE_EVENT(data, obj_size);
                break;
            case MOTION_BUS:
                // PRINT_OBJ(i, number_of_objects, obj_start, MOTION_BUS);
                PARSE_MOTION_BUS(data, obj_size);
                break;
            case MOTION_FX:
                // PRINT_OBJ(i, number_of_objects, obj_start, MOTION_FX);
                PARSE_MOTION_FX(data, obj_size);
                break;
            case EFFECT:
                // PRINT_OBJ(i, number_of_objects, obj_start, EFFECT);
                PARSE_EFFECT(data, obj_size);
                break;
            case AUXILIARY_BUS:
                // PRINT_OBJ(i, number_of_objects, obj_start, AUXILIARY_BUS);
                PARSE_AUXILIARY_BUS(data, obj_size);
                break;
        }

        ifp = data_start + obj_size;
    }
    printf("\n");
}