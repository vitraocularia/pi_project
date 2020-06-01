#include "fileHandler.h"

const int newFileNameSize = 100;

bool saveFile(SF_INFO* fileInfo, float data[], sf_count_t frames)
{
    char newFileName[newFileNameSize];
    char newPath[newFileNameSize + 8] = "out/";
    char* extension = ".wav";

    printf("Enter a name of the new file:\n");
    scanf("%s", newFileName);

    strcat(newPath, newFileName);
    strcat(newPath, extension);

    SNDFILE* saveFile = sf_open(newPath, SFM_WRITE, fileInfo);

    sf_writef_float(saveFile, data, frames);

    int res = sf_close(saveFile);

    if(res == 0)
    {
        printf("File saved successfully.\n");
        return true;
    }

    return false;
}

void quitProgram(float data[], SNDFILE* originalFile)
{
    free(data);
    sf_close(originalFile);
    exit(0);
}