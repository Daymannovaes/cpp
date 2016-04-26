#include <stdio.h>
#include <stdlib.h>

void printTable(int **table, int n, int m) {
	int i, j;

	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++) {
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	int n, m, k;
	int i, j;

	int **table;
	char ch;

	scanf("%d %d %d", &n, &m, &k);
	while(n != 0 || m != 0 || k != 0) {
		table = malloc(n * sizeof(int *));

		for(i = 0; i < n; i++) {
			table[i] = malloc(m * sizeof(int));

			for(j = 0; j < m; j++) {
				scanf("%c", &ch);

				if(ch == '.')
					table[i][j] = -2; // -2 represents uncovered
				else
					table[i][j] = atoi(ch);
			}
		}
		printTable(table, n, m);


		for(i = 0; i < n; i++) {
			free(table[i]);
		}
		free(table);
	}
  return 0;
}