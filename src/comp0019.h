#include <stdio.h>
#include "comp0019lib.h"

#ifndef COMP3007_H
#define COMP3007_H

#ifdef __cplusplus
extern "C" {
#endif

// Reads nucleobases from a file, compresses them into bytes and and writes the
// compressed version to the file stream 'out_file'.
void Encode(FILE* in_file, FILE* out_file);

// Extend this file as you see fit, but do not change the definitions above.

#ifdef __cplusplus
}
#endif

#endif  // Include guard
