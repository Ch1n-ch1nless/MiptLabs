#include "not_cmp_sorts.h"

const int MAX_PREF_SIZE = 256;

void LeastSignificantDigitSort(int* const src_array, const size_t array_size)
{
    assert((src_array != NULL) && "Pointer to \'src_array\' is NULL!!!\n");

    int* res_array = (int*) calloc(array_size, sizeof(int));
    assert((res_array != NULL) && "Program can not allocate memory!\n");

    unsigned int mask  = 0xff;  // bit mask to take 1 byte of number
    unsigned int shift = 0;     // shift of bytes

    while (mask > 0)
    {
        unsigned int pref_byte_cnt[MAX_PREF_SIZE] = {};
        for (int i = 0; i < MAX_PREF_SIZE; i++)
        {
            pref_byte_cnt[i] = 0;
        }
        
        for (int i = 0; i < array_size; i++)
        {
            pref_byte_cnt[(src_array[i] & mask) >> shift]++;
        }

        for (int i = 1; i < MAX_PREF_SIZE; i++)
        {
            pref_byte_cnt[i] += pref_byte_cnt[i-1];
        }


        for (int i = 1; i <= array_size; i++)
        {
            res_array[--pref_byte_cnt[(src_array[array_size - i] & mask) >> shift]] = src_array[array_size - i];
        }

        for (int i = 0; i < array_size; i++)
        {
            src_array[i] = res_array[i];
        }

        mask <<= 8;
        shift += 8;
    }

    free(res_array);
}

static void CountSort(int* const src_array, size_t array_size, int shift)
{
    assert((src_array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    if (array_size == 0) return;

    int  pref_count[MAX_PREF_SIZE] = {0};
    int* res_array = (int*) calloc(array_size, sizeof(int));
    assert((res_array != NULL) && "Program can not allocate memory!\n");

    int bit_mask = 0xff << shift;

    for (int i = 0; i < array_size; i++)
    {
        pref_count[(src_array[i] && bit_mask) >> shift]++;
    }

    for (int i = 1; i < 256; i++)
    {
        pref_count[i] += pref_count[i-1];
    }

    for (int i = array_size-1; i > -1; i--)
    {
        res_array[--pref_count[(src_array[i] && bit_mask) >> shift]] = src_array[i];
    }

    for (int i = 0; i < array_size; i++)
    {
        src_array[i] = res_array[i];
    }

    free(res_array);

    if (shift > 0) {
        CountSort(src_array, pref_count[0], shift - 8);
        for (size_t i = 1; i < MAX_PREF_SIZE; i++) {
            CountSort(src_array + pref_count[i - 1], pref_count[i] -pref_count[i - 1], shift - 8);
        }
    }
}

void MostSignificantDigitSort(int* const array, const size_t array_size)
{
    assert((array != NULL) && "Pointer to \'array\' is NULL!!!\n");

    CountSort(array, array_size, 8 * (sizeof(int)) - 1);
}