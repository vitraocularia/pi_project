#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sndfile.h>

void saveFile(SF_INFO* , float [], sf_count_t);
void quitProgram(SNDFILE*);