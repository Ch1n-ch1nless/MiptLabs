#ifndef HEAP_SORT_H_INCLUDED
#define HEAP_SORT_H_INCLUDED

#include "../testing.h"

struct Heap
{
    int* data;
    int  size;
    int  capacity;
    int  children;
};

/*===Declaration_of_sortings===*/

void    HeapSort(int* const array, const int array_size, const int number_of_childrens);

/*=============================*/

FILE*   OpenFile(const char* const dir_path, const size_t cur_size, const size_t k, const char* const extension, const char* const mode);

void    TestCorrectnessOfSortings(const char* const dir_path, const size_t from, const size_t to, 
                               const size_t step, FILE* time_list, size_t number_of_repetitions,
                               int number_of_children,
                               void (*sort_function) (int* const array, const int array_size, const int number_of_children));

/*=============================*/

#endif