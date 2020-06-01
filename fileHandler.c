#include "fileHandler.h"

const int newFileNameSize = 100;

void saveFile(SF_INFO* fileInfo, float data[], sf_count_t frames)
{
    char newFileName[newFileNameSize];
    char newPath[newFileNameSize + 8] = "out/";
    char* extension = ".wav";

    printf("Enter a name of the new file:\n");
    scanf("%s", newFileName);

    strcat(newPath, newFileName);
    strcat(newPath, extension);

    // printf("%s", newPath);

    printf("frames: %lld", frames);

    SNDFILE* saveFile = sf_open(newPath, SFM_WRITE, fileInfo);

    sf_writef_float(saveFile, data, frames);

    sf_close(saveFile);

    printf("File saved successfully.\n");
}

void quitProgram(float data[], SNDFILE* originalFile)
{
    free(data);
    sf_close(originalFile);
    exit(0);
}