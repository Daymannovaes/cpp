#include <stdio.h>
#include <stdlib.h>

void testCase(int, int);

int main() {
    setbuf(stdout, NULL);

    int **table;

    int testCount;
    int tableSize, keysCount;

    scanf("%d", &testCount);

    int indexI, indexJ, key;
    int i, j, k;
    for(i=0; i<testCount; i++) {
        scanf("%d %d", &tableSize, &keysCount);

        table = malloc(keysCount * sizeof(int*));
        for(j=0; j<keysCount; j++) {
            table[j] = malloc(tableSize * sizeof(int));

            for(k=0; k<tableSize; k++) {
                table[j][k] = -1;
            }
        }

        for(j=0; j<keysCount; j++) {
            scanf("%d", &key);
            indexJ = key%tableSize;
            indexI = 0;

            while(table[indexI][indexJ] != -1) indexI++;
            table[indexI][indexJ] = key;

            // printf("\ntable[%d][%d] = %d\n", indexI, indexJ, key);
        }

        for(j=0; j<tableSize; j++) {
            printf("%d -> ", j);
            indexI = 0;

            while(indexI < keysCount && table[indexI][j] != -1) {
                printf("%d -> ", table[indexI][j]);
                indexI++;
            }
            printf("\\\n");
        }

        if(i+1 != testCount) printf("\n");
    }

    return 0;
}
