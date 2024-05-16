#ifndef FENWICK_TREE_H_INCLUDED
#define FENWICK_TREE_H_INCLUDED

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*=================CONSTANTS==================*/

const size_t    MAX_NUMBER_OF_ELEMENTS  = 1000000;

const int       MODULE                  = 10000000;

/*==================STRUCTS===================*/

typedef struct Request
{
    int left;
    int right;
} Request;

typedef struct FenwickTree
{
    int*    data;
    size_t  size;
} FenwickTree;

/*=================FUNCTIONS==================*/

/*v~~~~~~~~~~~~~ARGUMENT PARSER~~~~~~~~~~~~~~v*/

void    ReadArguments(int argc, const char** argv, const char** file_with_numbers, const char** file_with_requests);

/*^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^*/

/*v~~~~~~~~~~~~~~~FENWICK TREE~~~~~~~~~~~~~~~v*/

FenwickTree*    FenwickTreeCtor(size_t init_size, int* array);
void            FenwickTreeDtor(FenwickTree* fenwick_tree);

int             FenwickTreeGetSum(FenwickTree* fenwick_tree, int start);

void            FenwickTreeUpdate(FenwickTree* fenwick_tree, int index, int delta);
int             FenwickTreeFindSum(FenwickTree* fenwick_tree, int left, int right);

/*^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^*/

/*v~~~~~~~~~~~~~EXECUTE REQUESTS~~~~~~~~~~~~~v*/

int*            ReadArrayWithNumbers(const char* const filename, size_t number_of_elements);
Request*        ReadArrayWithRequests(const char* const filename, size_t number_of_elements);

/*^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^*/

/*v~~~~~~~~~~~~~~~MEASURE TIME~~~~~~~~~~~~~~~v*/

double          MeasureTimeOfRequests(  FenwickTree*    fenwick_tree,
                                        Request*        request_array,
                                        size_t          number_of_requests);

/*^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^*/

#endif