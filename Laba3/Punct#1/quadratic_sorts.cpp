#include "testing.h"

void BubbleSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    int isSorted = FALSE;       // flag that shows is sorted array or not
    int temp = 0;               // temporary variable

    for (size_t i = 0; i < array_size && !isSorted; i++)
    {
        isSorted = TRUE;

        for (size_t j = 0; j < (array_size - i - 1); j++)
        {
            if (array[j] > array[j+1])
            {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                isSorted = FALSE;
            }
        }
    }
}

void InsertionSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    int temp = 0;   // temporary variable

    for (size_t i = 0; i < array_size; i++)
    {
        size_t j = i - 1;

        while (j >= 0 && array[j] > array[j+1])
        {
            // Swap values of array[j] & array[j+1]
            temp = array[j];
            array[j] = array[j+1];
            array[j+1] = temp;
            j--;
        }
    }
}

void SelectionSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    size_t min_index    = 0;    // index of minimal element
    int    temp         = 0;    // temporary variable

    for (size_t i = 0; i < array_size; i++)
    {
        min_index = i;

        for (size_t j = i + 1; j < array_size; j++)
        {
            if (array[min_index] > array[j])
            {
                min_index = j;
            }
        }

        // Swap values of array[i] & array[min_index]
        temp = array[min_index];
        array[min_index] = array[i];
        array[i] = temp;
    }
}