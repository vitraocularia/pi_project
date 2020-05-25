#include <stdio.h>
#include <sndfile.h>
#include "modifyingFunctions.h"
#include "helpers.h"

int main(int argc, char const *argv[])
{
    char* path = "sounds/bell.wav";
    SF_INFO fileInfo; 
    SNDFILE* file = sf_open(path, SFM_READ, &fileInfo);

    int frames = fileInfo.frames;
    size_t size = fileInfo.channels * frames;
    float data[size];

    float reversedData[size];

    float sortedData[size];
    copyTable(data, sortedData, size);
    quicksort(sortedData, 0, size - 1);

    sf_count_t framesCount = sf_readf_float(file, data, frames);

    reverseTable(data, reversedData, size);

    SNDFILE* saveFile = sf_open("out/reversedSound.wav", SFM_WRITE, &fileInfo);

    sf_writef_float(saveFile, reversedData, frames);

    sf_close(saveFile);

    saveFile = sf_open("out/sortedSound.wav", SFM_WRITE, &fileInfo);
    sf_writef_float(saveFile, sortedData, frames);

    sf_close(saveFile);

    sf_close(file);

    printf("Hello World!");
    return 0;
}
