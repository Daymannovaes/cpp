#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_CITIES 51

int graph[MAX_CITIES][MAX_CITIES];
int visited[MAX_CITIES];

void read_bridges(int bridgeCount);

void dfs();
void _dfs(int v);

void reset_visited();
void reset_graph();

void remove_bridge(int x, int y);
void insert_bridge(int x, int y);
bool is_graph_connected(int cityCount);


int main(int argc, char **argv) {
	int cityCount, bridgeCount;
	int cicledBridges;
	int x, y;
	int i;
	
	while(!feof(stdin)) {
		cicledBridges = 0;
		reset_graph();
		
		scanf("%d %d", &cityCount, &bridgeCount);
		
		read_bridges(bridgeCount);

		for(x=0; x<MAX_CITIES; x++) {
			for(y=x+1; y<MAX_CITIES; y++) {
				if(graph[x][y]) {
					remove_bridge(x, y);
					
					if(is_graph_connected(cityCount))
						cicledBridges++;
						
					insert_bridge(x, y);
				}
			}
		}
		
		printf("%d\n", bridgeCount - cicledBridges);
	}
}

void read_bridges(int bridgeCount) {
	int i;
	int x, y;

	for(i=0; i<bridgeCount; i++) {
		scanf("%d %d", &x, &y);
		
		graph[x-1][y-1] = graph[y-1][x-1] = 1;
	}
}

void dfs() {
	reset_visited();
 	_dfs(0);
}
void _dfs(int v) {
	int i;
 	visited[v] = 1;
 	
 	for(i=0; i<MAX_CITIES; i++) {
	 	if(!visited[i] && graph[v][i]) {
 			_dfs(i);
	 	}
 	}
}
void reset_visited() {
	int i;
 	for(i=0; i<MAX_CITIES; i++) {
 		visited[i] = false;
 	}
}

void reset_graph() {
	int i, j;
 	for(i=0; i<MAX_CITIES; i++) {
 		for(j=0; j<MAX_CITIES; j++) {
 			graph[i][j] = 0;
 		}
 	}
}

void remove_bridge(int x, int y) {
	graph[x][y] = 0;
	graph[y][x] = 0;
}
void insert_bridge(int x, int y) {
	graph[x][y] = 1;
	graph[y][x] = 1;
}

bool is_graph_connected(int cityCount) {
	int i;
	int connectedCities = 0;
	
	dfs();
	
	for(i=0; i <MAX_CITIES; i++) {
	 	if(visited[i])
			connectedCities++;
 	}
 	
 	return connectedCities == cityCount;
}