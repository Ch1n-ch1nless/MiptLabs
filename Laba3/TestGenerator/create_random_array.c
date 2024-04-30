#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ReadArguments(const int argc, const char** argv, int* const first_arg, int* const second_arg, const char** filename, int* const seed);
int  TranslateStringToNumber(const char* const string);

int main(int argc, const char* argv[])
{
    int array_size  = 0;
    int max_value   = RAND_MAX;
    int seed        = 0;
    const char* filename = NULL;

    ReadArguments(argc, argv, &array_size, &max_value, &filename, &seed);

    FILE* file_output = fopen(filename, "w");

    srand(seed);

    for (int i = 0; i < array_size; i++)
    {
        fprintf(file_output, "%d ", rand() % max_value);
    }

    return 0;
}

void ReadArguments(const int argc, const char** argv, int* const first_arg, int* const second_arg, const char** filename, int* const seed)
{
    assert((argc == 5 || argc == 4) && "You have put incorrect number of arguments!\n");
    assert((argv != NULL)           && "Pointer to \"argv\" is NULL!!!\n");

    *first_arg  = TranslateStringToNumber(argv[1]);

    if (argc == 5)
    {
        *second_arg = TranslateStringToNumber(argv[2]);
        *filename = argv[3];
        *seed = TranslateStringToNumber(argv[4]);
        return;
    }

    *filename = argv[2];
    *seed = TranslateStringToNumber(argv[3]);

    return;
}

int TranslateStringToNumber(const char* const string)
{
    assert((string != NULL) && "Pointer to \"string\" is NULL!!!\n");

    int index = 0;
    int number = 0;

    while (string[index] != '\0')
    {
        assert(('0' <= string[index] && string[index] <= '9') && "Program has got not number!!!\n");

        number *= 10;
        number += string[index] - '0';

        index++;
    }

    return number;
}