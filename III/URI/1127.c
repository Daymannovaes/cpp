#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ASIZE 257
#define MAXCHAR 257

int stopReading(int, int);
void readMusic(int, int **);
void flatToSharp(char *);

int calculateDist(char *, char *);

char isPlagiarism(int, int *, int, int *);

// 0 1 2 3 4 5 6 7 8 9 10 11 12 13
// D G A B C D G G G C D  E  F# G C C
// C  D G G
// 10 0 5 5
// G G C D



char *notes[12] = {"A",  "A#", "B", "C",  "C#", "D",
                   "D#", "E",  "F", "F#", "G",  "G#"};
// 0 1 2 3 4 5 6
// 0 2 3 5 7 8 10
//   0 2 4 5 7

void BMHPreprocess(int *snip, int T, int shiftTable[]) {
  int i, s;
  // printf("\nst\n");
  for (i = 0; i <= ASIZE; i++) {
    shiftTable[i] = 1;
  }
  for (i = 1; i < T; i++) {
    s = T - i;
    shiftTable[snip[i]] = s <= 0 ? 1 : s;
    // printf("[%d] = %d ", snip[i], shiftTable[snip[i]]);
  }

  // printf("\nst\n");
}

char BMH(int *snip, int T, int *music, int M) {
  int i, j, k, shiftTable[ASIZE];

  BMHPreprocess(snip, T, shiftTable);
  
  i = T; // snip size
  while (i <= M) {
    k = i;
    j = T;

      // printf("\nf[%d](%d) == [%d](%d)", k-1, music[k-1], j-1, (snip[j-1] + music[k-1 - (j-1)])%12);
    while ((music[k-1] == (snip[j-1] + music[k-1 - (j-1)])%12 || mod(music[k-1] - (snip[j-1] + music[k-1 - (j-1)])%12) == 12) && j > 0) {
      // printf("\nd[%d](%d) == [%d](%d)", k-1, music[k-1], j-1, (snip[j-1] + music[k-1 - (j-1)])%12);
      k--; j--;
      // printf("\nd[%d](%d) == [%d](%d)", k-1, music[k-1], j-1, (snip[j-1] + music[k-1 - (j-1)])%12);
    }
    if (j == 0) return 'S';
    
    // printf("\nst i-1=%d [%d] = %d\n", i-1, music[i-1], shiftTable[music[i-1]]);
    i += shiftTable[music[i-1]];
  }
  
  return 'N';
}

int mod(int n) {
  return n < 0 ? -n : n;
}

void BMH2(char *T, long n, char *P, long m)
{ long i, j, k, d[MAXCHAR + 1];
  for (j = 0; j <= MAXCHAR; j++) { d[j] = m; }
  for (j = 1; j < m; j++) { d[P[j-1]] = m - j; printf("\n\nJ = %d\nP[j-1] = %d(%c)\nd[P[j-1]] = %d", j, P[j-1], P[j-1], m-j); }
  i = m;
  while (i <= n)    /*-- Pesquisa --*/
    { k = i;
      j = m;
      while (T[k-1] == P[j-1] && j > 0) { k--; j--; }
      if (j == 0) 
      printf("Casamento na posicao: %3ld\n", k);
      i += d[T[i-1]];
    }
}



int main() {
  setbuf(stdout, NULL);

  while(1) {
    char a[64], b[64];
    gets(a);
    gets(b);

    BMH2(a, strlen(a), b, strlen(b));
  }

  return 0;

  // M is the length of the music
  // T is the length of the snippet
  int M = 0, T = 0;

  int *song = NULL, *snip = NULL;
  scanf("%d %d", &M, &T);

  do {
    readMusic(M, &song);
    readMusic(T, &snip);
    
    printf("%c\n", BMH(snip, T, song, M));

    // printf("%c\n", isPlagiarism(M, song, T, snip));
    scanf("%d %d", &M, &T);
  } while (!stopReading(M, T));

  return 0;
}

int stopReading(int M, int T) { return M == 0 && T == 0; }

void readMusic(int len, int **music) {
  int i;
  char baseNote[3]; // all distances are calculated from the first note
  char note[3]; // max of 2 chars + \0

  (*music) = malloc(len * sizeof(int));
  (*music)[0] = 0;
  
  for (i = 0; i < len; i++) {
    if(i == 0) {
      scanf("%s", baseNote);
      
      if(baseNote[1] == 'b')
        flatToSharp(baseNote); // ensure there is no flat format
    }
    else {  
      scanf("%s", note);

      if(note[1] == 'b')
        flatToSharp(note); // ensure there is no flat format

      (*music)[i] = calculateDist(baseNote, note);

    }
  }
}

// converts Db to C#, for example
void flatToSharp(char *note) {
  int i, index;

  for (i = 0; i < 12; i++) {
    if (note[0] == notes[i][0]) {     // Db match D, for example
      index = (i == 0 ? 11 : i - 1);  // Ab = G#, for example
      strcpy(note, notes[index]);
      return;
    }
  }
}

int calculateDist(char *baseNote, char *note) {
  int baseIndex, index;
  int find = 0;
  
  int i;

  for(i=0; i<12; i++) {
    if(strcmp(baseNote, notes[i]) == 0) {
      baseIndex = i;
      find++;
    }
    if(strcmp(note, notes[i]) == 0) {
      index = i;
      find++;
    }
    if(find == 2) {
      int value = index - baseIndex; // distance
      value = value >= 0 ? value : 12 + value; // always positive

      return value == 12 ? 0 : value; // 12 equals 0
    }
  }

  return -123456; // debug purpose
}

char isPlagiarism(int M, int *song, int T, int *snip) {
  int i;
  int offset, reset;

  for (i = 0; i < M; i++) {
    reset = 0;
    offset = 0;
    
    while(!reset) {
      // printf("\nsong[%d + %d] (%d) == snip[%d] + song[%d] (%d)\n", i, offset, song[i + offset], offset, i, snip[offset] + song[i]);
      if(song[i + offset] == (snip[offset] + song[i])
        || mod(song[i + offset] - (snip[offset] + song[i])) == 12)
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

  return 'N';
}