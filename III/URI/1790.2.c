#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_CITIES 50

int graph[MAX_CITIES][MAX_CITIES];
int visited[MAX_CITIES];

void dfs(int v) {
	int i;
 	visited[v]=1;
 	
 	for(i = 0; i < MAX_CITIES; ++i) {
	 	if(graph[v][i]) {
	 		if(visited[i] != 1) {
	 			dfs(i);
	 		}
	 	}
 	}
}

int is_graph_connected(int cityCount) {
	int i, connectedCities = 0;
	
	memset(visited, 0, sizeof(int) * MAX_CITIES);
	
	dfs(0);
	
	for(i = 0; i < MAX_CITIES; ++i) {
	 	if(visited[i])
			connectedCities += 1;
 	}
 	
 	return connectedCities == cityCount;
}

int main(int argc, char **argv) {
	while(1) {
		memset(graph, 0, MAX_CITIES * MAX_CITIES * sizeof(int));
	
	int cityCount, bridgeCount;
	if (scanf("%d%d", &cityCount, &bridgeCount) != 2)
		exit(0);
	
	int uncicledBridges = 0;
	
	int i;
	for(i = 0; i < bridgeCount; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		
		graph[x - 1][y - 1] = graph[y - 1][x - 1] = 1;
	}
	
	int x, y;
	for(x = 0; x < MAX_CITIES; ++x) {
		for(y = x+1; y < MAX_CITIES; ++y) {
			if(graph[x][y] == 1) {
				graph[x][y] = graph[y][x] = 0;
				
				if(!is_graph_connected(cityCount))
					uncicledBridges += 1;
					
				graph[x][y] = graph[y][x] = 1;
			}
		}
	}
	
	printf("%d\n", uncicledBridges);
	}
}