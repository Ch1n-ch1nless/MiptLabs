#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void    ReadArguments(const int argc, const char** argv, int* const first_arg, const char** filename);
int     TranslateStringToNumber(const char* string);
int     CompareNumbers(const void* number1, const void* number2);

int main(int argc, const char* argv[])
{
    srand(time(NULL));

    int         number_od_elems = 0;
    const char* file_name       = NULL;

    ReadArguments(argc, argv, &number_od_elems, &file_name);

    FILE* file = fopen(file_name, "w");
    assert((file != NULL) && "ERROR!!! PRogram can not open file!\n");

    int* array = (int*) calloc(number_od_elems, sizeof(int));
    assert((array != NULL) && "ERROR!!! Program can not allocate memory!\n");

    for (int i = 0; i < number_od_elems; i++)
    {
        array[i] = rand();
    }

    qsort(array, number_od_elems, sizeof(int), CompareNumbers);

    for (int i = 0; i < number_od_elems; i++)
    {
        fprintf(file, "%d ", array[i]);
    }
    
    free(array);
    fclose(file);

    return 0;
}

void ReadArguments(const int argc, const char** argv, int* const first_arg, const char** filename)
{
    assert((argc == 3)      && "ERROR!!! You have put incorrect number of arguments!\n");
    assert((argv != NULL)   && "ERROR!!! Pointer to \"argv\" is NULL!!!\n");

    *first_arg  = TranslateStringToNumber(argv[1]);

    *filename = argv[2];

    return;
}

int TranslateStringToNumber(const char* string)
{
    assert((string != NULL) && "ERROR!!! Pointer to \"string\" is NULL!!!\n");

    int index = 0;
    int number = 0;

    while (string[index] != '\0')
    {
        assert(('0' <= string[index] && string[index] <= '9') && "ERROR!!! Program has got not number!!!\n");

        number *= 10;
        number += string[index] - '0';

        index++;
    }

    return number;
}

int CompareNumbers(const void* number1, const void* number2)
{
    assert((number1 != NULL) && "ERROR!!! Pointer to \'number1\' is NULL!\n");
    assert((number2 != NULL) && "ERROR!!! Pointer to \'number2\' is NULL!\n");

    return *((int*)number1) - *((int*)number2);
}