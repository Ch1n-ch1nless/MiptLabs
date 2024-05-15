#include "test_log.h"

int main(int argc, const char* argv[])
{
    srand(SEED);

    const char* filename = NULL;

    ReadArguments(argc, argv, &filename);

    FILE* output = fopen(filename, "w");
    assert((output != NULL) && "ERROR!!! Program can not open!\n");

    CreateRandomElements(output);

    fclose(output);
}

void ReadArguments(int argc, const char** argv, const char** filename)
{
    assert((argc == 2)          && "ERROR!!! Invalid value of argc!\n");
    assert((argv != NULL)       && "ERROR!!! Invalid value of argv!\n");
    assert((filename != NULL)   && "ERROR!!! Invalid value of filename!\n");

    *filename   = argv[1];
}

void CreateRandomElements(FILE* output)
{
    assert((output != NULL) && "ERROR!!! Invalid value of output!\n");

    for (size_t i = 0; i < NUMBER_OF_ELEMENTS; i++)
    {
        fprintf(output, "%d ", rand() % MAX_VALUE);
    }
    
}