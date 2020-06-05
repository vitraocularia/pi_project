#include "modifyingFunctions.h"

void volModify(float table[], size_t from, size_t to, float startMultipler, float multiplerMod);

void swap(float* a, float* b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

/* This function reverses the order of the sounds in given interval.*/

void reverseTable(float table[], size_t from, size_t to)
{
    size_t modificationSize = to - from + 1;

    for (size_t i = 0; i < modificationSize/2; i++)
    {
        swap(&table[from + i], &table[to - i]);
    }
}

/* This functions overwrites the first positions in the array with data from chosen interval;
it returns the size of the interval, so we can reallocate the memory for the data array.*/

size_t extractPartOfATable(float table[], size_t from, size_t to)
{
    size_t newSize = to - from + 1;

    for (size_t i = 0; i < newSize; i++)
    {
        table[i] = table[from + i];
    }

    return newSize;
}

/* These two functions allow to gradually change the volume of the sound by changing the amplitude.*/

void volDecrease(float table[], size_t from, size_t to)
{
    volModify(table, from, to, 1.0, -0.01);
}

void volIncrease(float table[], size_t from, size_t to)
{
    volModify(table, from, to, 0.0, 0.01);
}

/* In this function we divide the data array into 100 segments of equal size and we change the amplitude in each segment
by multiplying it by a multiplier. After each segment we change the value of the multiplier, so the difference in volume
of two adjacent segments is about 1%. Depending on the startMultiplier value, we multiply the reamining amplitudes by 0% or 
100%.*/

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