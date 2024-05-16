#ifndef SPARSE_TABLE_H_INCLUDED
#define SPARSE_TABLE_H_INCLUDED

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN(a, b) (a < b) ? a : b

/*=================CONSTANTS==================*/

const size_t    MAX_NUMBER_OF_ELEMENTS  = 1000000;

const int       MODULE                  = 10000000;

/*==================STRUCTS===================*/

typedef struct Request
{
    int left;
    int right;
} Request;

struct SparseTable
{
    int*    log2;
    int**   data;
    size_t  size;
};

/*=================FUNCTIONS==================*/

/*v~~~~~~~~~~~~~ARGUMENT PARSER~~~~~~~~~~~~~~v*/

void    ReadArguments(int argc, const char** argv, const char** file_with_numbers, const char** file_with_requests);

/*^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^*/

/*v~~~~~~~~~~~~~~~SPARSE TABLE~~~~~~~~~~~~~~~v*/

SparseTable*    SparseTableCtor(int* array, size_t array_size);
void            SparseTableDtor(SparseTable* sparse_table);

int             SparseTableFindMin(SparseTable* sparse_table, int left, int right);

/*^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^*/

/*v~~~~~~~~~~~~~EXECUTE REQUESTS~~~~~~~~~~~~~v*/

int*            ReadArrayWithNumbers(const char* const filename, size_t number_of_elements);
Request*        ReadArrayWithRequests(const char* const filename, size_t number_of_elements);

/*^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^*/

/*v~~~~~~~~~~~~~~~MEASURE TIME~~~~~~~~~~~~~~~v*/

double          MeasureTimeOfRequests(  SparseTable*    sparse_table,
                                        Request*        request_array,
                                        size_t          number_of_requests);

/*^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^*/

#endif