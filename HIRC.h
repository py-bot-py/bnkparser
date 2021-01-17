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



#define PRINT_OBJ(_,__,___) ;
#ifdef DEBUG
#undef PRINT_OBJ
#define PRINT_OBJ(count, obj_start, type) \
    printf("Obj#%d @%d: %s\n", count, obj_start, #type);
#endif