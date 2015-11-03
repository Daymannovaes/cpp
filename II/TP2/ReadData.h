#ifndef _READDATA_H
#define _READDATA_H

#include "Talk.h"

void removeNewLine(char *str);
void readData(FILE *file);
char *readLineFrom(FILE *file);

// ---- parse functions
int defineMaxBatchesWithoutMessage(FILE *file);

#endif
