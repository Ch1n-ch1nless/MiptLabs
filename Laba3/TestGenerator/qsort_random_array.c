#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void ReadArguments(const int argc, const char** argv, int* const argument, const char** file_input_name, const char** file_output_name);
int  TranslateStringToNumber(const char* const string);
int  Compare(const void* const elem1, const void* const elem2);

int main(int argc, const char* argv[])
{
    int array_size = 0;
    const char* file_input_name = NULL;
    const char* file_output_name = NULL;

    ReadArguments(argc, argv, &array_size, &file_input_name, &file_output_name);

    FILE* file_input  = fopen(file_input_name, "r");
    FILE* file_output = fopen(file_output_name, "w");

    int* array = (int*) calloc(array_size, sizeof(int));
    assert((array != NULL) && "Pointer to \"array\" is NULL!!!\n");

    for (int i = 0; i < array_size; i++)
    {
        fscanf(file_input, "%d", array + i);
    }

    qsort(array, array_size, sizeof(int), Compare);

    for (int i = 0; i < array_size; i++)
    {
        fprintf(file_output, "%d ", array[i]);
    }

    return 0;
}

void ReadArguments(const int argc, const char** argv, int* const argument, const char** file_input_name, const char** file_output_name)
{
    assert((argc == 4)      && "You have put incorrect number of arguments!\n");
    assert((argv != NULL)   && "Pointer to \"argv\" is NULL!!!\n");

    *argument  = TranslateStringToNumber(argv[1]);

    *file_input_name  = argv[2];
    *file_output_name = argv[3];

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

int Compare(const void* const elem1, const void* const elem2)
{
    assert((elem1 != NULL) && "Pointer to \"elem1\" is NULL!!!\n");
    assert((elem2 != NULL) && "Pointer to \"elem2\" is NULL!!!\n");

    return *(int*) elem1 - *(int*) elem2;
}