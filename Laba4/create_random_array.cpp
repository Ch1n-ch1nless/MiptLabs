#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SEED  = 42;

void    ReadTheArguments(int argc, const char* argv[], const char** filename, size_t* array_size);
int     TranslateStringToNumber(const char* string);

int main(int argc, const char* argv[])
{
    srand(SEED);

    const char* filename    = NULL;
    size_t      array_size  = 0;

    ReadTheArguments(argc, argv, &filename, &array_size);

    FILE* outfile   = fopen(filename, "w");
    assert((outfile != NULL) && "Program can not open the file!\n");

    for (int i = 0; i < array_size; i++)
    {
        fprintf(outfile, "%d ", rand());
    }

    return 0;
}

void ReadTheArguments(int argc, const char* argv[], const char** filename, size_t* array_size)
{
    assert((argc == 3)          && "ERROR! Invalid value of the \'argc\'!!!\n");
    assert((argv != NULL)       && "ERROR! Invalid value of the \'argv\'!!!\n");
    assert((filename != NULL)   && "ERROR! Pointer to \'filename\' is NULL!!!\n");
    assert((array_size != NULL) && "ERROR! Pointer to \'array_size\' is NULL!!!\n");

    *array_size = TranslateStringToNumber(argv[1]);
    *filename   = argv[2];
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