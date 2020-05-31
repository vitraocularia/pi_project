#include <stdio.h>
#include <sndfile.h>
#include "helpers.h"

int getLengthInSeconds(SF_INFO * fileInfo)
{
    return fileInfo->frames / fileInfo->samplerate + 1;
}

void getIntervalIndices(SF_INFO* fileInfo, size_t* from, size_t* to)
{
    int length;
    int firstSecond, lastSecond;

    length = getLengthInSeconds(fileInfo);
    getIntervalInSeconds(&firstSecond, &lastSecond, length);

    *from = (firstSecond) * fileInfo->samplerate * fileInfo->channels;
    *to = (lastSecond) * fileInfo->samplerate * fileInfo->channels;

    if (*to > fileInfo->channels*fileInfo->frames)
    {
        *to = fileInfo->channels*fileInfo->frames;
    }

}

void getIntervalInSeconds(int* firstSecond, int* lastSecond, int length)
{
    printf("Your file is %d seconds long.\nWhich seconds would you like to modify?\nFrom: ", length);
    *firstSecond = getValue(length, 0);
    printf("To: ");
    *lastSecond = getValue(length, *firstSecond + 1);
}

int getValue(int upper_limit, int lower_limit)
{
    int value;

    while(scanf("%d", &value) != 1 || (value < lower_limit || value > upper_limit))
    {
        printf("Enter a number from %d to %d:\n", lower_limit, upper_limit);
        fflush(stdin);
    }

    return value;
}