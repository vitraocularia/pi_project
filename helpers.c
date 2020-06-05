#include <stdio.h>
#include <sndfile.h>
#include "helpers.h"

/* This function counts the length of the file in seconds basing on the information in fileInfo struct.*/

int getLengthInSeconds(SF_INFO * fileInfo)
{
    return fileInfo->frames / fileInfo->samplerate + 1;
}

/* This function gets the seconds of sound file and changes them for correct indices in the data array.*/

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
        *to = fileInfo->channels*fileInfo->frames - 1;
    }

}


/* This function informs the user about the length of their file and asks for the first and the last second
in the interval that they choose to modify until they give correct numbers.*/

void getIntervalInSeconds(int* firstSecond, int* lastSecond, int length)
{
    printf("Your file is %d seconds long.\nWhich seconds would you like to modify?\nFrom: ", length);
    *firstSecond = getValue(0, length - 1);
    printf("To: ");
    *lastSecond = getValue(*firstSecond + 1, length);
}

int getValue(int lower_limit, int upper_limit)
{
    int value;

    while(scanf("%d", &value) != 1 || (value < lower_limit || value > upper_limit))
    {
        printf("Enter a number from %d to %d:\n", lower_limit, upper_limit);
        fflush(stdin);
    }

    return value;
}