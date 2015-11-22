#include <stdio.h>
#include <stdlib.h>
#include "Molecule.h"


int strIsMoleculePoint(char *str) {
    return strstr(str, "PROTEINA ") != NULL;
}


int MAX_MOLECULE_POINTS = 1000;
Molecule *createMolecule() {
   	Molecule *molecule = malloc(sizeof(Molecule));

    molecule->pointCounter = 0;
    molecule->point = malloc(MAX_MOLECULE_POINTS * sizeof(Point));

    return molecule;
}

void addMoleculePoint(Molecule *molecule, char *str) {
    char *delimiter = " ";

    strtok(str, delimiter);
    strtok(NULL, delimiter);

    Point *point = createPointFromStr(NULL);

    molecule->point[molecule->pointCounter] = *point;
    molecule->pointCounter++;
}
