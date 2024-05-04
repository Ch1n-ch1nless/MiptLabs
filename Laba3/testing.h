#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*============Structs_&_Constants=============*/

// Point on graphic with coordinates: (size of array; time of sorting this array)
typedef struct GraphicPoint
{
    size_t size;
    double time;
} GraphicPoint;

const char* const VERY_SMALL_TESTS_PATH     = "very_small_tests/";
const char* const SMALL_TESTS_PATH          = "small_tests/";
const char* const BIG_TESTS_PATH            = "big_tests/";
const char* const TEST_MOST_DUBLICATES_PATH = "test_most_dublicates/";

const int TRUE                  = 1;
const int FALSE                 = 0;

const int MAX_SIZE_OF_FILE_NAME = 128;

/*============================================*/

#endif
