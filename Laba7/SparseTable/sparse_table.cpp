#include "sparse_table.h"

void ReadArguments(int argc, const char** argv, const char** file_with_numbers, const char** file_with_requests)
{
    assert((argc == 3)                   && "ERROR!!! Invalid value of \'argc\'!\n");
    assert((argv != NULL)                && "ERROR!!! Invalid value of \'argv\'!\n");
    assert((file_with_numbers  != NULL)  && "ERROR!!! Invalid value of \'file_with_numbers\'!\n");
    assert((file_with_requests != NULL)  && "ERROR!!! Invalid value of \'file_with_requests\'!\n");

    *file_with_numbers  = argv[1];
    *file_with_requests = argv[2];
}

//----------------------------------------------

SparseTable* SparseTableCtor(int* array, size_t array_size)
{
    assert((array      != NULL) && "ERROR!!! Pointer to \'array\' is NULL!\n");
    assert((array_size != 0)    && "ERROR!!! Invalid value of \'array_size\'!\n");

    SparseTable* new_sparse_table = (SparseTable*) calloc(1, sizeof(SparseTable));
    assert((new_sparse_table != NULL) && "ERROR!!! Program can not allocate memory!\n");

    new_sparse_table->size  = array_size;

    new_sparse_table->log2  = (int*) calloc(new_sparse_table->size + 1, sizeof(int));
    assert((new_sparse_table->log2 != NULL) && "ERROR!!! Program can not allocate memory!\n");

    new_sparse_table->log2[0] = 0;

    for (size_t i = 1; i <= new_sparse_table->size; i++)
    {
        new_sparse_table->log2[i] = new_sparse_table->log2[i/2] + 1;
    }

#ifdef FIRST_VERSION

    new_sparse_table->data = (int**) calloc(new_sparse_table->log2[array_size], sizeof(int*));
    assert((new_sparse_table->data != NULL) && "ERROR!!! Program can not allocate memory!\n");

    for (int i = 0; i < new_sparse_table->log2[array_size]; i++)
    {
        new_sparse_table->data[i] = (int*) calloc(array_size, sizeof(int));
        assert((new_sparse_table->data[i] != NULL) && "ERROR!!! Program can not allocate memory!\n");
    }

    for (size_t i = 0; i < new_sparse_table->size; i++)
    {
        new_sparse_table->data[0][i] = array[i];
    }

    for (int i = 1; i < new_sparse_table->log2[array_size]; i++)
    {
        for (int j = 0; j + (1 << i) - 1 < array_size; j++)
        {
            new_sparse_table->data[i][j] = MIN(new_sparse_table->data[i-1][j], new_sparse_table->data[i-1][j + (1 << (i - 1))]);
        }
    }

#else

    new_sparse_table->data = (int**) calloc(array_size, sizeof(int*));
    assert((new_sparse_table->data != NULL) && "ERROR!!! Program can not allocate memory!\n");

    for (size_t i = 0; i < array_size; i++)
    {
        new_sparse_table->data[i] = (int*) calloc(new_sparse_table->log2[i] + 1, sizeof(int));
        assert((new_sparse_table->data[i] != NULL) && "ERROR!!! Program can not allocate memory!\n");
    }

    for (size_t i = 0; i < new_sparse_table->size; i++)
    {
        new_sparse_table->data[i][0] = array[i];
    }

    for (int i = 1; i <= new_sparse_table->log2[array_size]; i++)
    {
        for (int j = 0; j + (1 << i) - 1 < array_size; j++)
        {
            new_sparse_table->data[j][i] = MIN(new_sparse_table->data[j][i-1], new_sparse_table->data[j + (1 << (i - 1))][i-1]);
        }
    }

#endif

    return new_sparse_table;
}

void SparseTableDtor(SparseTable* sparse_table)
{
    assert((sparse_table != NULL) && "ERROR!!! Pointer to \'sparse_table\' is NULL!\n");

    free(sparse_table->data);
    free(sparse_table->log2);

    sparse_table->data  = NULL;
    sparse_table->log2  = NULL;
    sparse_table->size  = 0;

    free(sparse_table);
}

int SparseTableFindMin(SparseTable* sparse_table, int left, int right)
{
    assert((sparse_table != NULL) && "ERROR!!! Pointer to \'sparse_table\' is NULL!\n");

#ifdef FIRST_VERSION

    int k = sparse_table->log2[right - left + 1] - 1;
    return MIN(sparse_table->data[k][left], sparse_table->data[k][right - (1 << k) + 1]);

#else

    int k = sparse_table->log2[right - left + 1] - 1;
    return MIN(sparse_table->data[left][k], sparse_table->data[right - (1 << k) + 1][k]);

#endif
}

//----------------------------------------------

int* ReadArrayWithNumbers(const char* const filename, size_t number_of_elements)
{
    assert((filename            != NULL) && "ERROR!!! Pointer to \'filename\' is NULL!\n");
    assert((number_of_elements  != 0)    && "ERROR!!! Invalid value of \'number_of_elements\'!\n");

    FILE* input = fopen(filename, "r");
    assert((input != NULL) && "ERROR!!! Program can not open file!\n");

    int* array = (int*) calloc(number_of_elements, sizeof(int));

    for (size_t i = 0; i < number_of_elements; i++)
    {
        if (fscanf(input, "%d", array + i) == 0)
        {
            assert(false && "ERROR!!! Program can not read the number!\n");
        }
    }

    return array;
}

Request* ReadArrayWithRequests(const char* const filename, size_t number_of_elements)
{
    assert((filename            != NULL) && "ERROR!!! Pointer to \'filename\' is NULL!\n");
    assert((number_of_elements  != 0)    && "ERROR!!! Invalid value of \'number_of_elements\'!\n");

    FILE* input = fopen(filename, "r");
    assert((input != NULL) && "ERROR!!! Program can not open file!\n");

    Request* array = (Request*) calloc(number_of_elements, sizeof(Request));

    for (size_t i = 0; i < number_of_elements; i++)
    {
        if (fscanf(input, "%d %d", &(array [i].left), &(array[i].right)) == 0)
        {
            assert(false && "ERROR!!! Program can not read the number!\n");
        }
    }

    return array;
}

//----------------------------------------------

double MeasureTimeOfRequests(SparseTable* sparse_table, Request* request_array, size_t number_of_requests)
{
    assert((sparse_table        != NULL) && "ERROR!!! Pointer to \'segment_tree\' is NULL!\n");
    assert((request_array       != NULL) && "ERROR!!! Pointer to \'request_array\' is NULL!\n");
    assert((number_of_requests  != 0)    && "ERROR!!! Invalid value of \'number_of_requests\'!\n");

    double time = 0.0;

    int answer = 0;

    clock_t time_begin  = clock();

    for (size_t i = 0; i < number_of_requests; i++)
    {
        answer = SparseTableFindMin(sparse_table, request_array[i].left, request_array[i].right);
    }
    
    clock_t time_end    = clock();

    time = (double)(time_end - time_begin) / ((double) CLOCKS_PER_SEC / 1e3);

    return time;
}

//----------------------------------------------