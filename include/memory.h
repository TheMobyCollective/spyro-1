#ifndef __MEMORY_H
#define __MEMORY_H

#include <sys/types.h>

// Memcpy (4 byte aligned)
void Memcpy(void *out, void *in, int size);

// Memset (4 byte aligned)
void Memset(void *out, int value, int size);

// Memset (16 byte aligned)
void Memset16(void *out, int value, int size);

#endif
