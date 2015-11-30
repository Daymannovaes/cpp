#include <stdio.h>
#include <string.h>
#include "ReadData.h"

float defineEdge(FILE *file) {
    float edge;
    fscanf(file, "%f", &edge);

    return edge;
}

char *readLineFrom(FILE *file) {
    char str[1024];
    fgets(str, sizeof(str), file);
    removeNewLine(str);

    return str;
}
void removeNewLine(char *str) {
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

int strIsBinderName(char *str) {
    return strstr(str, "Nome: ") != NULL;
}
int strIsBinderPoint(char *str) {
    return strstr(str, "LIGANTE ") != NULL;
}
int strIsMoleculePoint(char *str) {
    return strstr(str, "PROTEINA ") != NULL;
}