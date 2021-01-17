#include <stdlib.h>

#define SETTINGS                        1
#define SFX_OR_VOICE                    2
#define EVENT_ACTION                    3
#define EVENT                           4
#define RANDOM_OR_SEQUENCE_CONTAINER    5
#define SWITCH_CONTAINER                6
#define ACTOR_MIXER                     7
#define AUDIO_BUS                       8
#define BLEND_CONTAINER                 9
#define MUSIC_SEGMENT                   10
#define MUSIC_TRACK                     11
#define MUSIC_SWITCH_CONTAINER          12
#define MUSIC_PLAYLIST_CONTAINER        13
#define ATTENUATION                     14
#define DIALOGUE_EVENT                  15
#define MOTION_BUS                      16
#define MOTION_FX                       17
#define EFFECT                          18
#define AUXILIARY_BUS                   20


void HIRC(u_int8_t *data, unsigned start, unsigned size);


#define PRINT_OBJ(_,__,___) ;
#ifdef DEBUG
#undef PRINT_OBJ
#define PRINT_OBJ(count, obj_start, type) \
    printf("Obj#%d @%d: %s\n", count, obj_start, #type);
#endif