#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sndfile.h>
#include <stdbool.h>

bool saveFile(SF_INFO* , float [], sf_count_t);
void quitProgram(float [], SNDFILE*);