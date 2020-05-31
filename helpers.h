#include <stdio.h>
#include <sndfile.h>

typedef struct limitInIndices limitInIndices;

void copyTable(float [], float [], size_t);

int getLengthInSeconds(SF_INFO*);

void getIntervalIndices(SF_INFO*, size_t*, size_t*);
void getIntervalInSeconds(int*, int*, int);
int getValue(int, int);

