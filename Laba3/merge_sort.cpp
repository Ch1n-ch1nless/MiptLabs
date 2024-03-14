#include "testing.h"

#define MIN(a, b) (a < b) ? a : b

static void _merge_arrays(int* const array, const size_t begin, const size_t middle, const size_t end)
{
    size_t it1     = 0;
    size_t it2     = 0;
    int* result = (int*)calloc(end - begin + 1, sizeof(int));

    while (begin + it1 < middle && middle + it2 < end)
    {
        if (array[begin + it1] < array[middle + it2])
        {
            result[it1 + it2] = array[begin + it1];
            it1++;
        }
        else
        {
            result[it1 + it2] = array[middle + it2];
            it2++;
        }
    }

    while (begin + it1 < middle)
    {
        result[it1 + it2] = array[begin + it1];
        it1++;
    }

    while (middle + it2 < end)
    {
        result[it1 + it2] = array[middle + it2];
        it2++;
    }

    for (int i = 0; i < it1 + it2; i++)
    {
        array[begin + i] = result[i];
    }
    free(result);
}

static void _merge_sort(int* const array, const size_t begin, const size_t end)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");
    assert((begin <= end) && "Incorrect values of begin and end!!!\n");

    if (begin == end) return;

    size_t middle = begin + (end - begin) / 2;

    _merge_sort(array, begin, middle + 1);
    _merge_sort(array, 1 + middle, end + 1);
    _merge_arrays(array, begin, middle + 1, end + 1);
}

void RecursiveMergeSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    if (array_size == 0) return;

    _merge_sort(array, 0, array_size - 1);
}

void IterativeMergeSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

     for (size_t i = 1; i < array_size; i *= 2)
     {
        for (size_t j = 0; j < array_size - i; j += 2 * i)
        {
            _merge_arrays(array, j, j + i, MIN(j + 2 * i, array_size));
        }
     }
}