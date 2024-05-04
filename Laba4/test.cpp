#include "binary_heap.h"

void ReadTheArguments(int argc, char* argv[], size_t* buffer_size, const char** file_in, const char** file_out);
int TranslateStringToNumber(const char* const string);

int main(int argc, char* argv[])
{
    size_t      buffer_size = 0;
    const char* file_in     = NULL;
    const char* file_out    = NULL;

    ReadTheArguments(argc, argv, &buffer_size, &file_in, &file_out);

    FILE* file_in_ptr = fopen(file_in, "r");
    assert((file_in_ptr != NULL) && "ERROR! Program can not read the file!!!\n");

    FILE* file_out_ptr = fopen(file_out, "a");
    assert((file_out_ptr != NULL) && "ERROR! Program can not read the file!!!\n");

    node_t* buffer = (node_t*) calloc(buffer_size, sizeof(buffer));
    assert((buffer != NULL) && "ERROR! Program can not allocate memory!!!\n");

    //Fill buffer
    for (size_t i = 0; i < buffer_size; i++)
    {
        if (fscanf(file_in_ptr, "%d", buffer + i) == 0)
        {
            assert(0 && "ERROR! Program can not read the number!!!\n");
        }
    }

    fclose(file_in_ptr);

    BinaryHeap* heap = BinaryHeapCtor(INITIAL_CAPACITY);

    clock_t time_begin  = clock();

    #ifndef LINEAR_BUILD
        BinaryHeapBuildForNlogN(heap, buffer, buffer_size);
    #else
        BinaryHeapBuildForN(heap, buffer, buffer_size);
    #endif

    clock_t time_end    = clock();

    double time = ((double)(time_end - time_begin)) / (CLOCKS_PER_SEC / 1000);

    fprintf(file_out_ptr, "%lu, %lg\n", buffer_size, time);

    BinaryHeapDtor(heap);
    fclose(file_out_ptr);
    free(buffer);
}

void ReadTheArguments(int argc, char* argv[], size_t* buffer_size, const char** file_in, const char** file_out)
{
    assert((argc == 4)           && "ERROR! Invalid value of the \'argc\'!!!\n");
    assert((argv != NULL)        && "ERROR! Invalid value of the \'argv\'!!!\n");
    assert((file_in != NULL)     && "ERROR! Pointer to \'file_in\' is NULL!!!\n");
    assert((buffer_size != NULL) && "ERROR! Pointer to \'array_size\' is NULL!!!\n");

    *buffer_size = TranslateStringToNumber(argv[1]);
    *file_in    = argv[2];
    *file_out   = argv[3];
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