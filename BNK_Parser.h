#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "HIRC.h"


#define COPY(var, source, type, ifp) memcpy(&var, source+ifp, sizeof(type)); ifp += sizeof(type);

short UINT32_S;


typedef u_int8_t byte;


typedef struct _BKHD_Section
{
    size_t location;
    unsigned size;
    unsigned version;
    unsigned id;
} BKHD_Section;

typedef struct _DIDX_Section
{} DIDX_Section;
typedef struct _DATA_Section
{} DATA_Section;
typedef struct _ENVS_Section
{} ENVS_Section;
typedef struct _FXPR_Section
{} FXPR_Section;
typedef struct _STID_Section
{} STID_Section;
typedef struct _STMG_Section
{} STMG_Section;


typedef struct _BNK
{
    BKHD_Section* BKHD;
    DIDX_Section* DIDX;
    DATA_Section* DATA;
    ENVS_Section* ENVS;
    FXPR_Section* FXPR;
    HIRC_Section* HIRC;
    STID_Section* STID;
    STMG_Section* STMG;
} BNK;


size_t g_fsize;
unsigned g_ifp;
BNK g_bnk;