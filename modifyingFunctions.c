#include "modifyingFunctions.h"

const size_t SIZE_T_MAX = 18446744073709551615;

size_t partition(float table[], size_t left, size_t right);
void volModify(float table[], size_t from, size_t to, float startMultipler, float multiplerMod);


void swap(float* a, float* b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverseTable(float table[], size_t from, size_t to)
{
    size_t modificationSize = to - from + 1;

    for (size_t i = 0; i < modificationSize/2; i++)
    {
        swap(&table[from + i], &table[to - i]);
    }
}

size_t extractPartOfATable(float table[], size_t from, size_t to)
{
    size_t newSize = to - from + 1;

    for (size_t i = 0; i < newSize; i++)
    {
        table[i] = table[from + i];
    }

    return newSize;
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

void volDecrease(float table[], size_t from, size_t to)
{
    volModify(table, from, to, 1.0, -0.01);
}

void volIncrease(float table[], size_t from, size_t to)
{
    volModify(table, from, to, 0.0, 0.01);
}

void volModify(float table[], size_t from, size_t to, float startMultipler, float multiplerMod)
{
    size_t modificationSize = to - from + 1;

    int sectionSize = modificationSize/100;
    size_t index;

    float multiplier = startMultipler;

    for (size_t i = 0; i < 100; i++)
    {
        index = i * sectionSize;

        for (size_t j = 0; j < sectionSize; j++)
        {
            table[ from + index + j] *= multiplier;
        }

        multiplier += multiplerMod;
    }

    multiplier += multiplerMod;

    for (size_t i = index + sectionSize; i < modificationSize; i++)
    {
        table[from + i] *= multiplier;
    }
}