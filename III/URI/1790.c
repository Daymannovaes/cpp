#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_CITIES 51

typedef struct Bridge {
	int to;

	int inCicle;					// was this bridge counted in cicle algoritm
} Bridge;

typedef struct City {
	int id;
	int count;						// how many conneted cities

	Bridge bridges[MAX_CITIES];		// connected cities

	int pos;						// used in search algoritm
} City;

int cicle_bridges(City *initial, int pos);
int _cicle_bridges(City *initial, City *parent, City city, int pos);
void mark_bridge(int from, int to);
void unmark_bridge(int from, int to);

City cities[MAX_CITIES];
int BRIDGE_CICLE;
int main(int argc, char const *argv[]) {
    setbuf(stdout, NULL);

	int cityCount, bridgeCount;
	int x, y;
	int i, j;
	
	while(!feof(stdin)) {
    	BRIDGE_CICLE = 0;
		scanf("%d %d", &cityCount, &bridgeCount);

		for(i=0; i<cityCount; i++) {
			cities[i].count = 0;
			cities[i].id = i;
			cities[i].pos = 0;

			for(j=0; j<cityCount; j++) {
				cities[i].bridges[j].inCicle = false;
			}

		}

		// read
		i = bridgeCount;
		while(i) {
			scanf("%d %d", &x, &y);

			cities[x-1].bridges[cities[x-1].count].to = y-1;
			cities[x-1].count++;
			
			cities[y-1].bridges[cities[y-1].count].to = x-1;
			cities[y-1].count++;

			i--;
		}

		int cicleBridges = 0, pos;
		for(i=0; i<cityCount; i++) {
			pos = i+1;
			cicleBridges += cicle_bridges(&(cities[i]), pos);
		}
		printf("%d\n", bridgeCount - BRIDGE_CICLE);
	}

	return 0;
}

int cicle_bridges(City *initial, int pos) {
	if(initial->count <= 1) return 0;

	int i;
	int count = 0, partial;
	City next;

	initial->pos = pos;


	for(i=0; i<initial->count; i++) {
		next = cities[initial->bridges[i].to];
		partial = _cicle_bridges(initial, initial, next, pos);

		if(partial != -1) {
			count += partial;

			if(!cities[initial->id].bridges[i].inCicle) {
				count++;
				mark_bridge(initial->id, next.id);
			}
		}
	}

	return count;
}

int _cicle_bridges(City *initial, City *parent, City city, int pos) {
	int i;
	int count = 0;
	int partial;
	Bridge bridge;
	City next;

	if(city.id == initial->id) return 0; // fechou um ciclo
	if(cities[city.id].pos == pos) return -1; // ja passou por aqui
	if(city.count == 1) return -1; // impossivel continuar

	cities[city.id].pos = pos;

	for(i=0; i<city.count; i++) {
		bridge = city.bridges[i];
		next = cities[bridge.to];

		//printf("\nnext id %d parent id %d\n", next.id, parent->id);
		if(next.id != parent->id) {
			partial = _cicle_bridges(initial, &city, next, pos);

			if(partial != -1) {
				count += partial;

				if(!cities[city.id].bridges[i].inCicle) {
					count++;
					mark_bridge(city.id, next.id);
				}
			}
		}
	}

	cities[city.id].pos = 0;

	return count ? count : -1; // nenhum filho chegou ao inicial
}

void mark_bridge(int from, int to) {
	int i;
	for(i=0; cities[from].count; i++) {
		if(cities[from].bridges[i].to == to) {
			cities[from].bridges[i].inCicle = true;
			break;
		}
	}
	for(i=0; cities[to].count; i++) {
		if(cities[to].bridges[i].to == from) {
			cities[to].bridges[i].inCicle = true;
			break;
		}
	}

	BRIDGE_CICLE++;
}

void unmark_bridge(int from, int to) {
	int i;
	for(i=0; cities[from].count; i++) {
		if(cities[from].bridges[i].to == to) {
			cities[from].bridges[i].inCicle = false;
			break;
		}
	}
	for(i=0; cities[to].count; i++) {
		if(cities[to].bridges[i].to == from) {
			cities[to].bridges[i].inCicle = false;
			break;
		}
	}
}
