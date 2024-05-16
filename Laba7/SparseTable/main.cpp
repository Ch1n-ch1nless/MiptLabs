#include "sparse_table.h"

int main(int argc, const char* argv[])
{
    const char* file_with_numbers   = NULL;
    const char* file_with_requests  = NULL;

    size_t size = MAX_NUMBER_OF_ELEMENTS;

    ReadArguments(argc, argv, &file_with_numbers, &file_with_requests);

    int*     number_array   = ReadArrayWithNumbers(file_with_numbers, size);

    Request* request_array  = ReadArrayWithRequests(file_with_requests, size);

    SparseTable* sparse_table = SparseTableCtor(number_array, size);

    double time  = MeasureTimeOfRequests(sparse_table, request_array, size);

    printf("%lf\n", time);

    SparseTableDtor(sparse_table);

    free(number_array);
    free(request_array);

    return 0;
}