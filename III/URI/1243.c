#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printByCount(int);
int readAndCalculate(char*, FILE*);
int calculate(char*);

void removeNewLine(char*);

int isWord(char*);
int wordlen(char*);

int main() {
 
    int count;
    char str[64];
    //FILE *file = fopen("input.txt", "r");;
    FILE *file = stdin;

    while(gets(str)) {
        count = readAndCalculate(str, file);
        
        printByCount(count);    
    }

    return 0;
}

void printByCount(int count) {
    if(count <= 3)
        printf("250\n");
    else if(count <= 5)
        printf("500\n");
    else
        printf("1000\n");
}

int readAndCalculate(char *str, FILE *file) {
    removeNewLine(str);
    
    return calculate(str);
}

int calculate(char *str) {
    char word[64];
    char *start, *end;

    int wordCount = 0;
    int wordLenght = 0;
    
    end = str-1;
    while(end != NULL) {
        start = end+1;
        end = strchr(start, ' ');

        if(end != NULL) {
            strncpy(word, start, end-start);
            word[end-start] = '\0';

            if(isWord(word)) {
                wordCount++;

                wordLenght += wordlen(word);
            }
        }
    }

    
    if(isWord(start)) {
        wordCount++;

        wordLenght += wordlen(start);
    }

    if(wordCount == 0) return 0;
    return wordLenght/wordCount;
}

int isWord(char *word) {
    int i;
    int len = strlen(word);

    if(len == 0)
        return 0;

    char ch;
    
    for(i=0; i<len; i++) {
        ch = word[i];
        
        // accepts dot in last char
        if(len > 1 && i == len-1 && ch == '.') {
            return 1;
        }
        if(!(ch>='a' && ch<='z') && !(ch>='A' && ch<='Z')) {
            return 0;
        }
    }

    return 1;
}

void removeNewLine(char *str) {
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

int wordlen(char *str) {
    int len = strlen(str);

    if(str[len - 1] == '.')
        len--;

    return len;
}