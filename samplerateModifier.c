#include "samplerateModifier.h"

const int sampleratesNumber = 12;
int samplerates[sampleratesNumber] = {8000, 11025, 16000, 22050, 44100, 48000, 88200, 96000, 176400, 192000, 352800, 384000};

void printSampleratesMenu();


void changeSamplerate(SF_INFO* fileInfo)
{
    int newSamplerate = 0;

    printSampleratesMenu();

    while(scanf("%d", &newSamplerate) != 1 || (newSamplerate <= 0 || newSamplerate >= sampleratesNumber + 1))
    {
        printf("Enter a number from 1 to %d:\n", sampleratesNumber);
        fflush(stdin);
    }
    
    fileInfo->samplerate = samplerates[newSamplerate - 1];
}

void printSampleratesMenu()
{
    char* header = " -----------------\n";

    printf("Enter correct number to choose the samplerate:\n");
    printf("%s", header);
    printf("|NUMBER|SAMPLERATE|\n");

    for (int i = 0; i < sampleratesNumber; i++)
    {
        printf("|");
        printf("%6d", i+1);
        printf("|");
        printf("%10d", samplerates[i]);
        printf("|\n");
    }

    printf("%s", header);
}