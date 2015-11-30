#ifndef _READDATA_H
#define _READDATA_H

void removeNewLine(char *str);
char *readLineFrom(FILE *file);

int strIsBinderName(char *str);
int strIsBinderPoint(char *str);
int strIsMoleculePoint(char *str);
// ---- parse functions
float defineEdge(FILE *file);

#endif
