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

//