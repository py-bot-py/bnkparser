#include <stdlib.h>
#include <string.h>

#define COPY(var, source, type, ifp)  memcpy(&var, source+ifp, sizeof(type)); ifp += sizeof(type);

short UINT32_S;