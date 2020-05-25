#include <stdio.h>
#include <sndfile.h>
#include "modifyingFunctions.h"

int main(int argc, char const *argv[])
{
    char* path = "sounds/kobyla.wav";
    SF_INFO fileInfo; 
    SNDFILE* file = sf_open(path, SFM_READ, &fileInfo);

    int frames = fileInfo.frames;
    size_t size = fileInfo.channels * frames;
    float data[size];
    float result[size];

    sf_count_t framesCount = sf_readf_float(file, data, frames);

    // float* result = reverseTable(data, size);
    reverseTable(data, result, size);

    SNDFILE* saveFile = sf_open("out/sound.wav", SFM_WRITE, &fileInfo);

    sf_writef_float(saveFile, result, frames);

    sf_close(saveFile);
    sf_close(file);

    printf("Hello World!");
    return 0;
}
