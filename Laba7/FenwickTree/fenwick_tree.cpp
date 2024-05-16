#include "fenwick_tree.h"

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

FenwickTree* FenwickTreeCtor(size_t init_size, int* array)
{
    assert((init_size != 0)     && "ERROR!!! Invalid value of \'init_size\'!\n");
    assert((array     != NULL)  && "ERROR!!! Invalid value of \'array\'!\n");

    FenwickTree* new_fenwick_tree = (FenwickTree*) calloc(1, sizeof(FenwickTree));
    assert((new_fenwick_tree != NULL) && "ERROR!!! Program can not allocate memory!\n");

    new_fenwick_tree->data  = (int*) calloc(init_size, sizeof(int));
    assert((new_fenwick_tree->data != NULL) && "ERROR!!! Program can not allocate memory!\n");

    new_fenwick_tree->size  = init_size;

    for (size_t i = 0; i < new_fenwick_tree->size; i++)
    {
        FenwickTreeUpdate(new_fenwick_tree, i, array[i]);
    }

    return new_fenwick_tree;
}   

void FenwickTreeDtor(FenwickTree* fenwick_tree)
{
    assert((fenwick_tree != NULL) && "ERROR!!! Invalid value of \'fenwick_tree\' is NULL!\n");

    if (fenwick_tree->data != NULL)
    {
        for (size_t i = 0; i < fenwick_tree->size; i++)
        {
            fenwick_tree->data[i] = 0;
        }
    }

    free(fenwick_tree->data);

    fenwick_tree->data  = NULL;
    fenwick_tree->size  = 0;

    free(fenwick_tree);
}

int FenwickTreeGetSum(FenwickTree* fenwick_tree, int start)
{
    assert((fenwick_tree != NULL) && "ERROR!!! Pointer to \'fenwick_tree\' is NULL");

    int result = 0;

    for (int i = start; i >= 0; i = (i & (i + 1)) - 1)
    {
        result += fenwick_tree->data[i];
        result %= MODULE;
    }

    return result % MODULE;
}

void FenwickTreeUpdate(FenwickTree* fenwick_tree, int index, int delta)
{
    assert((fenwick_tree != NULL) && "ERROR!!! Pointer to \'fenwick_tree\' is NULL");

    for (int i = index; i < fenwick_tree->size; i = (i | (i + 1)))
    {
        fenwick_tree->data[i] += delta;
        fenwick_tree->data[i] %= MODULE;
    }
}

int FenwickTreeFindSum(FenwickTree* fenwick_tree, int left, int right)
{
    assert((fenwick_tree != NULL) && "ERROR!!! Pointer to \'fenwick_tree\' is NULL");

    int right_sum   = FenwickTreeGetSum(fenwick_tree, right);
    int left_sum    = FenwickTreeGetSum(fenwick_tree, left-1);

    return ((right_sum - left_sum) % MODULE + MODULE) % MODULE;
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

double MeasureTimeOfRequests(FenwickTree* fenwick_tree, Request* request_array, size_t number_of_requests)
{
    assert((fenwick_tree        != NULL) && "ERROR!!! Pointer to \'fenwick_tree\' is NULL!\n");
    assert((request_array       != NULL) && "ERROR!!! Pointer to \'request_array\' is NULL!\n");
    assert((number_of_requests  != 0)    && "ERROR!!! Invalid value of \'number_of_requests\'!\n");

    double time = 0.0;

    int answer = 0;

    for (int j = 0; j < 5; j++)
    {
        for (size_t i = 0; i < number_of_requests; i++)
        {
            clock_t time_begin  = clock();

            answer = FenwickTreeFindSum(fenwick_tree, request_array[i].left, request_array[i].right);

            clock_t time_end    = clock();

            time += (double)(time_end - time_begin) / ((double) CLOCKS_PER_SEC / 1e3);
        }
    }

    time /= 5.0;

    return time;
}