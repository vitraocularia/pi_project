#include "fileHandler.h"

const int newFileNameSize = 100;

/* This function asks the user for a name of their new sound file and saves it in the "out" directory.
It returns information if the file was saved successfully. 
We need this information in case the user forgets to save the file before calling quit function.*/

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

/* This function quits the program. Before doing so, it frees memory allocated for the data and closes the original file.*/

void quitProgram(float data[], SNDFILE* originalFile)
{
    free(data);
    sf_close(originalFile);
    exit(0);
}