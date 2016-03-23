#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stopReading(int, int);
void readMusic(int, char ***);
void flatToSharp(char *);

void stepUpKeyMusic(int, char **);
void stepUpKeyNote(char *);
char isPlagiarism(int, char **, int, char **);

char *notes[12] = {"A",  "A#", "B", "C",  "C#", "D",
                   "D#", "E",  "F", "F#", "G",  "G#"};

int main() {
  setbuf(stdout, NULL);

  // M is the length of the music
  // T is the length of the snippet
  int M = 0, T = 0;

  char **song = NULL, **snip = NULL;
  scanf("%d %d", &M, &T);

  do {
    readMusic(M, &song);
    readMusic(T, &snip);

    printf("%c\n", isPlagiarism(M, song, T, snip));
    scanf("%d %d", &M, &T);
  } while (!stopReading(M, T));

  return 0;
}

int stopReading(int M, int T) { return M == 0 && T == 0; }

void readMusic(int len, char ***music) {
  int i;

  (*music) = malloc(len * sizeof(char *));
  for (i = 0; i < len; i++) {
    (*music)[i] = malloc(3 * sizeof(char)); // max of 2 chars + \0

    scanf("%s", (*music)[i]);
    flatToSharp((*music)[i]); // ensure there is no flat format
  }
}

// converts Db to C#, for example
void flatToSharp(char *note) {
  int i, index;

  for (i = 0; i < 12; i++) {
    if (note[1] == 'b' && note[0] == notes[i][0]) { // Db match D, for example
      index = (i == 0 ? 11 : i - 1);                // Ab = G#, for example
      strcpy(note, notes[index]);
      return;
    }
  }
}

void stepUpKeyMusic(int len, char **music) {
  int i;

  for (i = 0; i < len; i++) {
    stepUpKeyNote(music[i]);
  }
}

void stepUpKeyNote(char *note) {
  int i, index;

  for (i = 0; i < 12; i++) {
    if (strcmp(note, notes[i]) == 0) {
      index = i == 11 ? 0 : i + 1; // step up
      strcpy(note, notes[index]);
      return;
    }
  }
}

char isPlagiarism(int M, char **song, int T, char **snip) {
  int i, j;
  int offset, reset;

  // 'j' is to test in every key
  for(j = 0; j < 12; j++) {
    for (i = 0; i < M; i++) {
      reset = 0;
      offset = 0;
      
      while(!reset) {
        if(strcmp(song[i + offset], snip[offset]) == 0)
          offset++;
        else {
          reset = 1;
        }

        if(offset == T) return 'S';
        if(i+T >= M) {
          break;
        }
      }

      if (offset == T)
        return 'S';
    }

    stepUpKeyMusic(T, snip);
  }

  return 'N';
}

int resetOffset(int M, char **song, int T, char **snip, int end, int offset) {
  if(offset == 0 || offset == 1)
    return 0;

  int i;
  int reset;

  while(offset != 0) {
    reset = 1;

    for(i=0; i<offset; i++) {
      if(strcmp(snip[i], song[end - offset + i]) != 0)
        reset = 0;
    }

    if(reset) return offset;
    offset--;
  }

  return offset;
}