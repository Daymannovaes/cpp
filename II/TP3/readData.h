#ifndef _READDATA_H
#define _READDATA_H

void removeNewLine(char *str);
char *readLineFrom(FILE *file);

// ---- parse functions
float defineEdge(FILE *file);

#endif
