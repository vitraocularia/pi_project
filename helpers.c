#include <stdio.h>
#include "helpers.h"

void copyTable(float table[], float result[], size_t tableSize)
{
    for (size_t i = 0; i < tableSize; i++)
    {
        result[i] = table[i];
    }
}