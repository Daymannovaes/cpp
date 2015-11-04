#include <stdio.h>
#include <string.h>
#include "ReadData.h"

char STOP_STR2[2] = "-1";
int stopReading2(FILE *file, char *str) {
    return feof(file) || !strcmp(str, STOP_STR2);
}

void readData(FILE *file) {
    char str[1024];

    do {

        fgets(str, sizeof(str), file);

        removeNewLine(str);
    } while(!stopReading2(file, str));
}

int defineMaxBatchesWithoutMessage(FILE *file) {
    int max;
    fscanf(file, "%d", &max);

    return max;
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
