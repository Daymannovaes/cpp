#ifndef _READDATA_H
#define _READDATA_H

#include "Talk.h"

void readData(FILE *file, Talk *talks);
char *readLineFrom(FILE *file);
void removeNewLine(char *str);

// ---- parse functions
int defineMaxBatchesWithoutMessage(FILE *file);

#endif
