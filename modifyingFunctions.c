#include "modifyingFunctions.h"

void swap(float* table, int i, int j)
{
    float tmp = table[i];
    table[i] = table[j];
    table[j] = tmp;
}

void reverseTable(float* table, float* result, size_t tableSize)
{
    for (size_t i = 0; i < tableSize; i++)
    {
        result[i] = table[tableSize - i - 1];
    }
}

void reverseTableRef(float * table, size_t tableSize)
{
    for (size_t i = 0; i < tableSize/2; i++)
    {
        swap(table, i, tableSize - i - 1);
    }
}