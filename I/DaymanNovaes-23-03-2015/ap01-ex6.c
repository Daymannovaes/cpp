#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int a, b, c;
    float delta;
    float x1, x2;

    printf("ax^2 + bx + c = 0\n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    delta = pow(b, 2) - (4*a*c);

    if(delta < 0)
        printf("Nao ha raizes reais.");
    else if(delta == 0) {
        x1 = (-b)/(2*a);
        printf("A unica raiz real e': %f", x1);
    }
    else {
        x1 = (-b + sqrt(delta))/(2*a);
        x2 = (-b - sqrt(delta))/(2*a);

        printf("As raizes sao: %f e %f", x1, x2);
    }

    return 0;
}
