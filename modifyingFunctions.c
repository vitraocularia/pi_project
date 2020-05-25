#include "modifyingFunctions.h"

const size_t SIZE_T_MAX = 18446744073709551615;

size_t partition(float table[], size_t left, size_t right);

void swap(float* a, float* b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverseTable(float table[], float result[], size_t tableSize)
{
    for (size_t i = 0; i < tableSize; i++)
    {
        result[i] = table[tableSize - i - 1];
    }
}

void reverseTableRef(float table[], size_t tableSize)
{
    for (size_t i = 0; i < tableSize/2; i++)
    {
        swap(&table[i], &table[tableSize - 1 - i]);
    }
}

void quicksort(float table[], size_t left, size_t right)
{
    if (left < right && right != SIZE_T_MAX)
    {
        size_t pivot = partition(table, left, right);
        quicksort(table, left, pivot-1);
        quicksort(table, pivot+1, right);
    }
}

size_t partition(float table[], size_t left, size_t right)
{
    float pivot_value = table[right];
    
    size_t i = left - 1;
    
    for (size_t j = left; j < right; j++)
    {
        if (table[j] < pivot_value)
        {
            i += 1;
            swap(&table[i], &table[j]);
        }
    }

    i += 1;
    swap(&table[i], &table[right]);
    return i;
}