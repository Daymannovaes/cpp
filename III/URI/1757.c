#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_CITIES 101

int graph[MAX_CITIES][MAX_CITIES];
int visited[MAX_CITIES];

void dfs(int v, int totalCities);

void reset_visited();
void reset_graph(int totalCities);
void read_graph(int visibleRoutes);
 
int main() {
    int testCount, routeCount;
    int totalCities, visibleRoutes;
    int i;
 
    scanf("%d", &testCount);
    while(testCount) {
        routeCount = 0;

        scanf("%d %d", &totalCities, &visibleRoutes);

        reset_graph(totalCities);
        read_graph(visibleRoutes);

        reset_visited();
        for(i=0; i<totalCities; i++) {
            if(!visited[i]) {
                dfs(i, totalCities);
                routeCount++;
            }
        }
 
        printf("%d\n", !routeCount ? routeCount : routeCount-1);
        testCount--;
    }
 
    return 0;
}

void dfs(int v, int totalCities) {
    int i;
    visited[v] = true;
    
    for(i=0; i<totalCities; i++) {
        if(!visited[i] && graph[v][i]) {
            dfs(i, totalCities);
        }
    }
}
void reset_visited() {
    int i;
    for(i=0; i<MAX_CITIES; i++) {
        visited[i] = false;
    }
}
void reset_graph(int totalCities) {
    int i, j;
    for(i=0; i<totalCities; i++) {
        for(j=0; j<totalCities; j++) {
            graph[i][j] = (i == j) ? 0 : 1;
        }
    }
}
void read_graph(int visibleRoutes) {
    int i, x, y;
    for(i=0; i<visibleRoutes; i++) {
        scanf("%d %d", &x, &y);

        graph[x][y] = 0;
        graph[y][x] = 0;
    }
}