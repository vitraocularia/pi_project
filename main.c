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


/* This functions allows to call the activity chosen by the user.*/

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
        isFileSaved = saveFile(fileInfo, data, *frames);
        sleep(2);
        break;
    case 60:
        printf("Choose to save the file.\n");
        sleep(3);
        break;
    case 7:
        if(isFileSaved == false)
        {
            printf("You haven't saved your file.\nDo you want to quit anyway?\n0 - no\n1 - yes\n");
            int quitDecision;
            while (scanf("%d", &quitDecision) != 1 || (quitDecision < 0 || quitDecision > 1))
            {
                printf("Enter 1 to quit or 0 to return to the main menu.\n");
                fflush(stdin);
            }
            if (quitDecision == 0)
            {
                break;
            }
        }
        quitProgram(data, file);
        break;
    case 70:
        printf("Choose to quit the program.\n" );
        sleep(3);
        break;
    default:
        break;
    }
}


int main(int argc, char const *argv[])
{    

    /* We get a correct path to the file that user wants to modify. As we open the file, we get the pointer
    to SNDFILE struct and we save some crucial information about the file in the SF_INFO struct.*/

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

    /* We need to allocate memory for the array data in which we will keep all amplitudes of the sound file.
    We get the information about the size of the array from the SF_INFO struct and we fill the array
    while calling sf_readf_float function.*/
    
    size_t size = fileInfo.frames * fileInfo.channels;
    sf_count_t frames = fileInfo.frames;

    float* data = (float*)malloc(size*sizeof(float));

    sf_count_t framesCount = sf_readf_float(file, data, fileInfo.frames);

    /* With all those information we may show the menu repeatedly until user decides to quit the program.*/

    while ( 1 )
    {
        printMainMenu();
        int activityNumber = getActivity();

        callActivity(file, &fileInfo, data, size, activityNumber, &frames);
    }

    return 0;
}
