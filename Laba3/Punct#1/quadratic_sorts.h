#ifndef QUADRATIC_SORTINGS_H_INCLUDED
#define QUADRATIC_SORTINGS_H_INCLUDED

#include "../testing.h"

/*===Declaration_of_sortings===*/

void    BubbleSort(int* const array, const size_t array_size);
void    InsertionSort(int* const array, const size_t array_size);
void    SelectionSort(int* const array, const size_t array_size);

void    ShellSort(int* const array, const size_t array_size);

/*=============================*/

FILE*   OpenFile(const char* const dir_path, const size_t cur_size, const size_t k, const char* const extension);

void    TestCorrectnessOfSortings(const char* const dir_path, const size_t from, const size_t to, 
                               const size_t step, FILE* time_list, size_t number_of_repetitions,
                               void (*sort_function) (int* const array, const size_t array_size));

/*=============================*/

#endif