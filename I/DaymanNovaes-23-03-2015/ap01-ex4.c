#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int x;
    short int y;
    unsigned char c;

    x = pow(2, 31) - 1;
    y = pow(2, 15) - 1;
    c = pow(2,  8) - 1;

    printf("Maior valores: \nx: %d\ty: %d: \tc: %d", x, y, c);

    x++;
    y++;
    c++;

    printf("\n\nMaior valores + 1: \nx: %d\ty: %d: \tc: %d", x, y, c);

    return 0;
}
