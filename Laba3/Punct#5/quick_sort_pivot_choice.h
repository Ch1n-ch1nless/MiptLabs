#ifndef QUICK_SORT_PIVOT_CHOICE_H
#define QUICK_SORT_PIVOT_CHOICE_H

#include "../testing.h"

/*===Declaration_of_sortings===*/

void    QuickSortWithCentralPivot(int* const array, const size_t array_size);
void    QuickSortWithMedianOf3Elements(int* const array, const size_t array_size);
void    QuickSortWithRandomPivot(int* const array, const size_t array_size);
void    QuickSortWithMedianOf3RandomElements(int* const array, const size_t array_size);

/*=============================*/

FILE*   OpenFile(const char* const dir_path, const size_t cur_size, const size_t k, const char* const extension);

void    TestCorrectnessOfSortings(  const char* const dir_path, const size_t from, const size_t to, 
                                    const size_t step, FILE* time_list, size_t number_of_repetitions,
                                    void (*sort_function) (int* const array, const size_t array_size) );

/*=============================*/


#endif