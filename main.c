#include <stdio.h>
#include <sndfile.h>
#include <unistd.h>
#include "modifyingFunctions.h"
#include "helpers.h"
#include "samplerateModifier.h"
#include "menuHandler.h"
#include "fileHandler.h"

const int pathSize = 1000;
bool isFileSaved = false;

struct limit
{
    size_t from;
    size_t to;

} interval;

struct table
{
    size_t size;
    float* data;
} table;

void callActivity(SNDFILE* file, SF_INFO * fileInfo, float data[], size_t size, int activityNumber, sf_count_t *frames)
{
    switch (activityNumber)
    {
    case 1:
        changeSamplerate(fileInfo);
        break;
    case 10:
        printf("This activity allows to change the frequency of the whole sound file.\n");
        sleep(3);
        break;
    case 2:
        getIntervalIndices(fileInfo, &interval.from, &interval.to);
        volDecrease(data, interval.from, interval.to);
        break;
    case 20:
        printf("This activity gradually decrases the volume of the whole sound file or its fragment.\n");
        sleep(3);
        break;
    case 3:
        getIntervalIndices(fileInfo, &interval.from, &interval.to);
        volIncrease(data, interval.from, interval.to);
        break;
    case 30:
        printf("This activity gradually increases the volume of the whole sound file or its fragment.\n");
        sleep(3);
        break;
    case 4:
        getIntervalIndices(fileInfo, &interval.from, &interval.to);
        size = extractPartOfATable(data, interval.from, interval.to);
        data = realloc(data, size * sizeof(float));
        fileInfo->frames = size / fileInfo->channels;
        *frames = fileInfo->frames;
        break;
    case 40:
        printf("This activity allows to extract a part of the sound file.\n");
        sleep(3);
        break;
    case 5:
        getIntervalIndices(fileInfo, &interval.from, &interval.to);
        reverseTable(data, interval.from, interval.to);
        break;
    case 50:
        printf("This activity reverses the whole sound file or its fragment.\n");
        sleep(3);
        break;
    case 6:
        quicksort(data, 0, size - 1);  
        break;
    case 60:
        printf("This activity sorts the whole sound file by the amplitude of the sounds.\n");
        sleep(3);
        break;
    case 7:
        isFileSaved = saveFile(fileInfo, data, *frames);
        break;
    case 70:
        printf("Choose to save the file.\n");
        sleep(3);
        break;
    case 8:
        if(isFileSaved)
        {
            quitProgram(data, file);
            break;
        }
    case 80:
        printf("Choose to quit the program.\nRemember to save your file first.\n" );
        sleep(3);
        break;
    default:
        break;
    }
}


int main(int argc, char const *argv[])
{    
    char filePath[pathSize];

    printf("Enter a path to your sound file:\n");
    scanf("%s", filePath);

    SF_INFO fileInfo;
    SNDFILE* file = sf_open(filePath, SFM_READ, &fileInfo);

    while (file == NULL)
    {
        printf("Wrong path. Please try again: \n");
        scanf("%s", filePath);
        file = sf_open(filePath, SFM_READ, &fileInfo);
    }

    printf("File opened successfully.\n");
    sleep(1);
    
    size_t size = fileInfo.frames * fileInfo.channels;
    sf_count_t frames = fileInfo.frames;

    float* data = (float*)malloc(size*sizeof(float));
    // float data[size];

    sf_count_t framesCount = sf_readf_float(file, data, fileInfo.frames);

    while ( 1 )
    {
        printMainMenu();
        int activityNumber = getActivity();

        callActivity(file, &fileInfo, data, size, activityNumber, &frames);
    }

    return 0;
}
