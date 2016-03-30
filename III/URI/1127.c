#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 12

int stopReading(int, int);
void readMusic(int, int **);
void flatToSharp(char *);

int indexOf(char *);

char isPlagiarism(int, int *, int, int *);
int calculateDist(int, int);

int shift[SIZE];
void calculateShifts(int, int *, int, int *);
int shiftOf(int);

                //  0     1     2    3     4     5    6     7     8    9    10     11
char *notes[12] = {"A",  "A#", "B", "C",  "C#", "D", "D#", "E",  "F", "F#", "G",  "G#"};

// D G  A B C D G  G  G  C D E F# G C C
// 5 10 0 2 3 5 10 10 10 3 5 7 9 10 3 3

// 5 10 0 2 3  5 10 10 10 3 5 7 9 10 3 3
// 5 2  2 1 2  5 0  0   5 2 2 2 1 5  0 -

// G  G  C D
// 10 10 3 5
// 0  5  2 -

int main() {
  setbuf(stdout, NULL);

  // M is the length of the music
  // T is the length of the snippet
  int M = 0, T = 0;

  int *song = NULL, *snip = NULL;
  scanf("%d %d", &M, &T);

  do {
    readMusic(M, &song);
    readMusic(T, &snip);

    if(T == 1)
      printf('N');
    else
      printf("%c\n", isPlagiarism(M-1, song, T-1, snip));

    scanf("%d %d", &M, &T);
  } while (!stopReading(M, T));

  return 0;
}

int stopReading(int M, int T) { return M == 0 && T == 0; }

void readMusic(int len, int **music) {
  int i;
  char note[3];
  (*music) = malloc(len * sizeof(int));
  for (i = 0; i < len; i++) {
    scanf("%s", note);

    if(note[1] == 'b')
      flatToSharp(note); // ensure there is no flat format, like Bb

    // printf("indexOf(%s) = %d\n", note, indexOf(note));
    (*music)[i] = indexOf(note);

    if(i > 0) {
      (*music)[i-1] = calculateDist((*music)[i], (*music)[i-1]);
      // printf("[%d]=(%d) ", i-1, (*music)[i-1]);
    }
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

int indexOf(char *note) {
  int i;
  for (i = 0; i < 12; i++) {
    if(strcmp(notes[i], note) == 0)
      return i;
  }

  printf("\ncan't find indexOf %s\n", note);
  return -1;
}

char isPlagiarism(int M, int *song, int T, int *snip) {
  int i, reset;
  calculateShifts(M, song, T, snip); // pre proccess

  // shift moves the snip along the music, like a slide
  int shift;

  // offset moves the pointer along the snip, while compare is matching
  // FROM END TO BEGIN
  int offset;

  int dist; // distance from music to snip

  i = T; // begin reading by the last char of the snip
  while(i <= M) {
    reset = 0;

    shift = i;
    offset = T;

    // while dist remains the same, keep comparing
    while(offset > 0 && song[shift-1] == snip[offset-1]) {
      shift--; offset--;
    }

    if (offset == 0) return 'S';
    
    // The dist is different, let's shift to match the same notes
    i += shiftOf(song[i-1]);
  }

  return 'N';
}

int calculateDist(int a, int b) {
  int dist = a - b;
  dist = dist >= 0 ? dist : 12+dist;

  // printf("\n||dist(%d, %d) = %d||\n", a, b, dist);
  return dist;
}

void calculateShifts(int M, int *song, int T, int *snip) {
  int i;

  // if the note doesn't exists in the snip, we'll shift the size of the snip
  for(i=0; i<SIZE; i++) shift[i] = T;

  // necessary shift to match next snip note with the given song note
  for(i=1; i<T; i++) shift[snip[i-1]] = T - i;
}

int shiftOf(int i) {
  return shift[i];
}