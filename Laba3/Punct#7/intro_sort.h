#ifndef SORTINGS_H_INCLUDED
#define SORTINGS_H_INCLUDED

#include "../testing.h"
#include <math.h>

typedef struct Heap
{
    int* data;
    int  size;
    int  capacity;
    int  children;
} Heap;

const size_t BLOCK_SIZE_FOR_SHELL_SORT  = 142;
const size_t NUMBER_OF_HEAP_CHILDREN    = 5;

/*===Declaration_of_sortings===*/

void    IntroSort(int* const array, const size_t array_size, const size_t depth_limit);

/*=============================*/

FILE*   OpenFile(const char* const dir_path, const size_t cur_size, const size_t k, const char* const extension);

void    TestCorrectnessOfSortings(  const char* const dir_path, const size_t from, const size_t to, 
                                    const size_t step, FILE* time_list, size_t number_of_repetitions,
                                    const size_t depth_limit,
                                    void (*sort_function) (int* const array, const size_t array_size, const size_t depth_limit) );

/*=============================*/

#endif