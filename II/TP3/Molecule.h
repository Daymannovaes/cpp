#ifndef _MOLECULE_H
#define _MOLECULE_H

#include "Point.h"

typedef struct {
    int pointCounter;
    Point *point;
} Molecule;


Molecule *createMolecule();

int strIsBinderName(char *str);
int strIsMoleculePoint(char *str);

#endif
