#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printTable(char **table, int n, int m) {
	return;
	int i, j;

	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++) {
			printf("%c", table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int countCovered(char **table, int n, int m, int i, int j) {
	int covered = 0;

	if(i-1 >= 0 && j-1 >= 0) // 1
		if(table[i-1][j-1] == '.' || table[i-1][j-1] == 'i') covered++;

	if(i-1 >= 0 && j >= 0) // 2
		if(table[i-1][j] == '.' || table[i-1][j] == 'i') covered++;

	if(i-1 >= 0 && j+1 <= m-1) // 3
		if(table[i-1][j+1] == '.' || table[i-1][j+1] == 'i') covered++;

	if(i >= 0 && j+1 <= m-1) // 4
		if(table[i][j+1] == '.' || table[i][j+1] == 'i') covered++;

	if(i+1 <= n-1 && j+1 <= m-1) // 5
		if(table[i+1][j+1] == '.' || table[i+1][j+1] == 'i') covered++;

	if(i+1 <= n-1 && j >= 0) // 6
		if(table[i+1][j] == '.' || table[i+1][j] == 'i') covered++;

	if(i+1 <= n-1 && j-1 >= 0) // 7
		if(table[i+1][j-1] == '.' || table[i+1][j-1] == 'i') covered++;

	if(i >= 0 && j-1 >= 0) // 8
		if(table[i][j-1] == '.' || table[i][j-1] == 'i') covered++;

	return covered;
}

int countSignaled(char **table, int n, int m, int i, int j) {
	int signaled = 0;

	if(i-1 >= 0 && j-1 >= 0) // 1
		if(table[i-1][j-1] == 'x') signaled++;

	if(i-1 >= 0 && j >= 0) // 2
		if(table[i-1][j] == 'x') signaled++;

	if(i-1 >= 0 && j+1 <= m-1) // 3
		if(table[i-1][j+1] == 'x') signaled++;

	if(i >= 0 && j+1 <= m-1) // 4
		if(table[i][j+1] == 'x') signaled++;

	if(i+1 <= n-1 && j+1 <= m-1) // 5
		if(table[i+1][j+1] == 'x') signaled++;

	if(i+1 <= n-1 && j >= 0) // 6
		if(table[i+1][j] == 'x') signaled++;

	if(i+1 <= n-1 && j-1 >= 0) // 7
		if(table[i+1][j-1] == 'x') signaled++;

	if(i >= 0 && j-1 >= 0) // 8
		if(table[i][j-1] == 'x') signaled++;

	return signaled;
}

int countMines(char **table, int n, int m, int i, int j) {
	int mines = 0;

	if(i-1 >= 0 && j-1 >= 0) { // 1
		if(table[i-1][j-1] == '.') return -1; // don't know how many mines
		if(table[i-1][j-1] == 'x' || table[i-1][j-1] == 'i') mines++;
	}

	if(i-1 >= 0 && j >= 0) { // 2
		if(table[i-1][j] == '.') return -1; // don't know how many mines
		if(table[i-1][j] == 'x' || table[i-1][j] == 'i') mines++;
	}

	if(i-1 >= 0 && j+1 <= m-1) { // 3
		if(table[i-1][j+1] == '.') return -1; // don't know how many mines
		if(table[i-1][j+1] == 'x' || table[i-1][j+1] == 'i') mines++;
	}

	if(i >= 0 && j+1 <= m-1) { // 4
		if(table[i][j+1] == '.') return -1; // don't know how many mines
		if(table[i][j+1] == 'x' || table[i][j+1] == 'i') mines++;
	}

	if(i+1 <= n-1 && j+1 <= m-1) { // 5
		if(table[i+1][j+1] == '.') return -1; // don't know how many mines
		if(table[i+1][j+1] == 'x' || table[i+1][j+1] == 'i') mines++;
	}

	if(i+1 <= n-1 && j >= 0) { // 6
		if(table[i+1][j] == '.') return -1; // don't know how many mines
		if(table[i+1][j] == 'x' || table[i+1][j] == 'i') mines++;
	}

	if(i+1 <= n-1 && j-1 >= 0) { // 7
		if(table[i+1][j-1] == '.') return -1; // don't know how many mines
		if(table[i+1][j-1] == 'x' || table[i+1][j-1] == 'i') mines++;
	}

	if(i >= 0 && j-1 >= 0) { // 8
		if(table[i][j-1] == '.') return -1; // don't know how many mines
		if(table[i][j-1] == 'x' || table[i][j-1] == 'i') mines++;
	}

	return mines;
}

int signify(char **table, int n, int m, int i, int j) {
	int signaled = 0;

	if(i-1 >= 0 && j-1 >= 0) // 1
		if(table[i-1][j-1] == '.' || table[i-1][j-1] == 'i') { table[i-1][j-1] = 'x'; signaled++; }

	if(i-1 >= 0 && j >= 0) // 2
		if(table[i-1][j] == '.' || table[i-1][j] == 'i') { table[i-1][j] = 'x'; signaled++; }

	if(i-1 >= 0 && j+1 <= m-1) // 3
		if(table[i-1][j+1] == '.' || table[i-1][j+1] == 'i') { table[i-1][j+1] = 'x'; signaled++; }

	if(i >= 0 && j+1 <= m-1) // 4
		if(table[i][j+1] == '.' || table[i][j+1] == 'i') { table[i][j+1] = 'x'; signaled++; }

	if(i+1 <= n-1 && j+1 <= m-1) // 5
		if(table[i+1][j+1] == '.' || table[i+1][j+1] == 'i') { table[i+1][j+1] = 'x'; signaled++; }

	if(i+1 <= n-1 && j >= 0) // 6
		if(table[i+1][j] == '.' || table[i+1][j] == 'i') { table[i+1][j] = 'x'; signaled++; }

	if(i+1 <= n-1 && j-1 >= 0) // 7
		if(table[i+1][j-1] == '.' || table[i+1][j-1] == 'i') { table[i+1][j-1] = 'x'; signaled++; }

	if(i >= 0 && j-1 >= 0) // 8
		if(table[i][j-1] == '.' || table[i][j-1] == 'i') { table[i][j-1] = 'x'; signaled++; }

	return signaled;
}

int tipify(char **table, int n, int m, int i, int j) {
	int tipified = 0, cm;

	if(i-1 >= 0 && j-1 >= 0) // 1
		if(table[i-1][j-1] == '.' || table[i-1][j-1] == 'i' || table[i-1][j-1] == '?') {
			cm = countMines(table, n, m, i-1, j-1);
			if(cm == -1) { table[i-1][j-1] = '?'; }
			else table[i-1][j-1] = cm + '0';
			tipified++;
		}

	if(i-1 >= 0 && j >= 0) // 2
		if(table[i-1][j] == '.' || table[i-1][j] == 'i' || table[i-1][j] == '?') {
			cm = countMines(table, n, m, i-1, j);
			if(cm == -1) { table[i-1][j] = '?'; }
			else table[i-1][j] = cm + '0';
			tipified++;
		}

	if(i-1 >= 0 && j+1 <= m-1) // 3
		if(table[i-1][j+1] == '.' || table[i-1][j+1] == 'i' || table[i-1][j+1] == '?') {
			cm = countMines(table, n, m, i-1, j+1);
			if(cm == -1) { table[i-1][j+1] = '?'; }
			else table[i-1][j+1] = cm + '0';
			tipified++;
		}

	if(i >= 0 && j+1 <= m-1) // 4
		if(table[i][j+1] == '.' || table[i][j+1] == 'i' || table[i][j+1] == '?') {
			cm = countMines(table, n, m, i, j+1);
			if(cm == -1) { table[i][j+1] = '?'; }
			else table[i][j+1] = cm + '0';
			tipified++;
		}

	if(i+1 <= n-1 && j+1 <= m-1) // 5
		if(table[i+1][j+1] == '.' || table[i+1][j+1] == 'i' || table[i+1][j+1] == '?') {
			cm = countMines(table, n, m, i+1, j+1);
			if(cm == -1) { table[i+1][j+1] = '?'; }
			else table[i+1][j+1] = cm + '0';
			tipified++;
		}

	if(i+1 <= n-1 && j >= 0) // 6
		if(table[i+1][j] == '.' || table[i+1][j] == 'i' || table[i+1][j] == '?') {
			cm = countMines(table, n, m, i+1, j);
			if(cm == -1) { table[i+1][j] = '?'; }
			else table[i+1][j] = cm + '0';
			tipified++;
		}

	if(i+1 <= n-1 && j-1 >= 0) // 7
		if(table[i+1][j-1] == '.' || table[i+1][j-1] == 'i' || table[i+1][j-1] == '?') {
			cm = countMines(table, n, m, i+1, j-1);
			if(cm == -1) { table[i+1][j-1] = '?'; }
			else table[i+1][j-1] = cm + '0';
			tipified++;
		}

	if(i >= 0 && j-1 >= 0) // 8
		if(table[i][j-1] == '.' || table[i][j-1] == 'i' || table[i][j-1] == '?') {
			cm = countMines(table, n, m, i, j-1);
			if(cm == -1) { table[i][j-1] = '?'; }
			else table[i][j-1] = cm + '0';
			tipified++;
		}

	return tipified;
}

int main() {
    setbuf(stdout, NULL);
	int n, m, k;
	int i, j;
	int a, b;

	int cc, cs; // count covered, count signaled

	char **table;
	char ch;
	int tip;

	int cm = 0; // count mines
	int pcm = cm; // previous cm

	scanf("%d %d %d", &n, &m, &k);
	while(n != 0 || m != 0 || k != 0) {
		table = malloc(n * sizeof(char *));

		for(i = 0; i < n; i++) {
			table[i] = malloc(m * sizeof(char));

			for(j = 0; j < m; j++) {
				scanf(" %c", &ch);

				if(ch == '.') cm++;

				table[i][j] = ch;
			}
		}
		printTable(table, n, m);

		for(i = 0; i < k; i++) {
			scanf("%d %d", &a, &b);

			table[a-1][b-1] = 'i'; // invisible mine for the user
		}
		printTable(table, n, m);

		int tst = 1000;
		int pos = 1;
		do {
			pcm = cm;

			for(i = 0; i < n; i++) {
				for(j = 0; j < m; j++) {
					ch = table[i][j];

					if(ch != '.' && ch != 'x' && ch != '?' && ch != 'i') {
						cc = countCovered(table, n, m, i, j);
						cs = countSignaled(table, n, m, i, j);
						tip = ch - '0'; // char to int
						if(tip == cc + cs) {
							// all covered are mines
							cm -= signify(table, n, m, i, j);
						}
						else if(tip == cs) {
							// all covered aren't mines
							cm -= tipify(table, n, m, i, j);
							tipify(table, n, m, i, j);
						}
						else if(tip > cc + cs) { // impossible!
							pos = 0;
							tst = -1;
							i = n; j = m;
							break;
						}
					}
					if(ch == '?') {
						tipify(table, n, m, i, j);
					}
				}
			}
			tst--;
		} while(tst > 0);

		if(pos)
			for(i = 0; i < n; i++) {
				for(j = 0; j < m; j++) {
					ch = table[i][j];

					if(ch == '.') {
						printf("Impossivel\n");
						i = n; j = m;
						pos = 0;
					}
				}
			}
		else
			printf("Impossivel\n");
		if(pos)
			printf("Possivel\n");

		printTable(table, n, m);

		for(i = 0; i < n; i++) {
			free(table[i]);
		}
		free(table);

		scanf("%d %d %d", &n, &m, &k);
	}
  return 0;
}