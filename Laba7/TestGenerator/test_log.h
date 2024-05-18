#ifndef TEST_LOH_H_INCLUDED
#define TEST_LOG_H_INCLUDED

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*=================CONSTANTS==================*/

const size_t    NUMBER_OF_ELEMENTS  = 1000000;
const int       SEED                = 42;
const int       MAX_VALUE           = 1000;

/*=================FUNCTIONS==================*/

void    ReadArguments(int argc, const char** argv, const char** filename);

void    CreateRandomElements(FILE* output);
void    CreateRandomRequests(FILE* output);

#endif