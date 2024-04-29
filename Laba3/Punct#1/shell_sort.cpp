#include "testing.h"

void ShellSort(int* const array, const int array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    size_t step = 1;

    while (step <= array_size / 9)
    {
        step = step * 3 + 1;
    }
    while (step > 0)
    {
        for (size_t i = step; i < array_size; i += step)
        {
            int temp = array[i];
            size_t j = i;

            while (j >= step && array[j - step] > temp)
            {
                array[j] = array[j - step];
                j -= step;
            }

            array[j] = temp;
        }

        step /= 3;
    }
}