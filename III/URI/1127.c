#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stopReading(int, int);
void readMusic(int, char**);
void flatToSharp(char*);

void stepUpKeyMusic(int, char**);
void stepUpKeyNote(char*);
char isPlagiarism(int, char**, int, char**);

char *notes[12] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};

int main() {
    //setbuf(stdout, NULL);
    
    // M is the length of the music
    // T is the length of the snippet
    int M, T;

    char **song, **snip;

    while(!stopReading(M, T)) {
        scanf("%d%d", &M, &T);

        readMusic(M, song);
        readMusic(T, snip);

        printf("%s\n", isPlagiarism(M, song, T, snip));
    }

    return 0;
}

int stopReading(int M, int T) {
    return M == 0 && T == 0;
}

void readMusic(int len, char **music) {
    int i;
    
    music = (char **)malloc(len * sizeof(char *));
    for(i=0; i<len; i++) {
        music[i] = (char *)malloc(2 * sizeof(char)); // max of 2 chars

        scanf("%s", music[i]);
        flatToSharp(music[i]); // ensure there is no flat format
    }
}

// converts Db to C#, for example
void flatToSharp(char *note) {
    int i, index;

    for(i=0; i<12; i++) {
        if(note[1] == 'b' && note[0] == notes[i][0]) { // Db match D, for example
            index = i == 0 ? 11 : i - 1; //Ab = G#, for example
            strcpy(note, notes[index]);
        }
    }
}

void stepUpKeyMusic(int len, char **music) {
    int i;
    
    for(i=0; i<len; i++) {
        stepUpKeyNote(music[i]);
    }
}
void stepUpKeyNote(char *note) {
    int i, index;

    for(i=0; i<12; i++) {
        if(strcmp(note, notes[i]) == 0) {
            index = i == 11 ? 0 : i + 1; // step up
            strcpy(note, notes[index]);
        }
    }
}

char isPlagiarism(int M, char **song, int T, char **snip) {
    int i, offset;


    offset = 0;

    for(i=0; i<M; i++) {
        printf("%s == %s ? \n", song[i], snip[offset]);
        if(strcmp(song[i], snip[offset]) == 0)
            offset++;
        else
            offset = 0;

        if(offset == T)
            return 'S';
    }

    return 'N';
}