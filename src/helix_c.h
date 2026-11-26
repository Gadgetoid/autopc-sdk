#ifndef AUTOPC_HELIX_C_H
#define AUTOPC_HELIX_C_H

#define _ASSEMBLY_H

#include <stddef.h>

void *malloc(size_t size);
void free(void *pointer);

typedef long long Word64;

static __inline int MULSHIFT32(int x, int y)
{
    return (int)(((Word64)x * y) >> 32);
}

static __inline Word64 MADD64(Word64 sum, int x, int y)
{
    return sum + (Word64)x * y;
}

static __inline Word64 SAR64(Word64 x, int n)
{
    return x >> n;
}

static __inline int FASTABS(int x)
{
    int sign = x >> (sizeof(int) * 8 - 1);
    return (x ^ sign) - sign;
}

static __inline int CLZ(int x)
{
    return x ? __builtin_clz((unsigned int)x) : (int)(sizeof(int) * 8);
}

#endif
